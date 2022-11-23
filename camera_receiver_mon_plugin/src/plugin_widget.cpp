/* ========================= LICENSE =================================
*
* Copyright (C) 2022 Continental Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* ========================= LICENSE =================================
*/

#include "plugin_widget.h"

#include <QClipboard>
#include <QMenu>
#include <QDebug>

PluginWidget::PluginWidget(const QString& topic_name, const QString& topic_type, QWidget* parent):
  QWidget(parent),
  compressed_image_subscriber_(topic_name.toStdString()),
  last_received_photo_(nullptr),
  last_message_publish_timestamp_(eCAL::Time::ecal_clock::time_point(eCAL::Time::ecal_clock::duration(-1))),
  topic_name_(topic_name),
  topic_type_(topic_type),
  new_msg_available_(false),
  received_message_counter_(0)
{
  ui_.setupUi(this);

  // Timestamp warning
  int label_height = ui_.publish_timestamp_warning_label->sizeHint().height();
  QPixmap warning_icon = QPixmap(":/ecalicons/WARNING").scaled(label_height, label_height, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
  ui_.publish_timestamp_warning_label->setPixmap(warning_icon);
  ui_.publish_timestamp_warning_label->setVisible(false);

  // Add eCAL Callbacks
  compressed_image_subscriber_.AddReceiveCallback(std::bind(&PluginWidget::photoReceivedMessageCallback, this, std::placeholders::_2, std::placeholders::_3));

}

PluginWidget::~PluginWidget()
{
#ifndef NDEBUG
  // call the function via its class becase it's a virtual function that is called in constructor/destructor,-
  // where the vtable is not created yet or it's destructed.
  qDebug().nospace() << "[" << PluginWidget::metaObject()->className() << "]: Deleting Widget for topic " << topic_name_;
#endif // NDEBUG

  compressed_image_subscriber_.RemReceiveCallback();

  {
    std::lock_guard<std::mutex> lock(proto_message_mutex_);
    delete last_received_photo_;
  }
}

void PluginWidget::updatePublishTimeLabel()
{
  eCAL::Time::ecal_clock::time_point publish_time = last_message_publish_timestamp_;
  eCAL::Time::ecal_clock::time_point receive_time = eCAL::Time::ecal_clock::now();

  if (publish_time < eCAL::Time::ecal_clock::time_point(eCAL::Time::ecal_clock::duration(0)))
    return;

  auto diff = receive_time - publish_time;

  if ((diff > std::chrono::milliseconds(100))
    || (diff < std::chrono::milliseconds(-100)))
  {
    ui_.publish_timestamp_warning_label->setVisible(true);
    QString diff_string = QString::number(std::chrono::duration_cast<std::chrono::duration<double>>(diff).count(), 'f', 6);
    ui_.publish_timestamp_warning_label->setToolTip(tr("The publisher is not synchronized, properly.\nCurrent time difference: ") + diff_string + " s");
  }
  else
  {
    ui_.publish_timestamp_warning_label->setVisible(false);
  }

  QString time_string;

  //if (parse_time_)
  //{
  //  QDateTime q_ecal_time = QDateTime::fromMSecsSinceEpoch(std::chrono::duration_cast<std::chrono::milliseconds>(publish_time.time_since_epoch()).count()).toUTC();
  //  time_string = q_ecal_time.toString("yyyy-MM-dd HH:mm:ss.zzz");
  //}
  //else
  {
    double seconds_since_epoch = std::chrono::duration_cast<std::chrono::duration<double>>(publish_time.time_since_epoch()).count();
    time_string = QString::number(seconds_since_epoch, 'f', 6) + " s";
  }

  ui_.publish_timestamp_label->setText(time_string);
}

////////////////////////////////////////////////////////////////////////////////
//// Content Update                                                         ////
////////////////////////////////////////////////////////////////////////////////

// eCAL Callback
void PluginWidget::photoReceivedMessageCallback(const foxglove::CompressedImage& compressed_image_msg, long long send_time_usecs)
{
  {
    // Lock the mutex
    std::lock_guard<std::mutex> lock(proto_message_mutex_);
    // Delete the old message
    delete last_received_photo_;

    // Create a copy of the new message as member variable. We cannot use a reference here, as this may cause a deadlock with the GUI thread
    last_received_photo_ = compressed_image_msg.New();
    last_received_photo_->CopyFrom(compressed_image_msg);

    eCAL::Logging::Log(eCAL_Logging_eLogLevel::log_level_info, "Received " + compressed_image_msg.format() + " photo of size " +
      std::to_string(last_received_photo_->data().length()));

    last_message_publish_timestamp_ = eCAL::Time::ecal_clock::time_point(std::chrono::duration_cast<eCAL::Time::ecal_clock::duration>(std::chrono::microseconds(send_time_usecs)));

    new_msg_available_ = true;
    received_message_counter_++;
  }
}

// Actual Content Update
void PluginWidget::updateContent()
{
  auto photo_data = last_received_photo_->data();
  QByteArray byte_array(photo_data.c_str(), photo_data.length());
  QPixmap pixmap;
  pixmap.loadFromData(byte_array, "JPG");

  ui_.photo_label->setPixmap(pixmap.scaled(ui_.photo_label->size(), Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation));

  new_msg_available_ = false;
}

void PluginWidget::onUpdate()
{
  if (new_msg_available_)
  {
    updateContent();
    updatePublishTimeLabel();
    ui_.received_message_counter_label->setText(QString::number(received_message_counter_));
  }
}

void PluginWidget::onResume()
{
  // Add eCAL Callbacks
  compressed_image_subscriber_.AddReceiveCallback(std::bind(&PluginWidget::photoReceivedMessageCallback, this, std::placeholders::_2, std::placeholders::_3));
}

void PluginWidget::onPause()
{
  compressed_image_subscriber_.RemReceiveCallback();
}

QWidget* PluginWidget::getWidget()
{
  return this;
}

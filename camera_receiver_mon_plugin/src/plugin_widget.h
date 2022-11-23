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

#pragma once

#include <ecal/mon/plugin.h>
#include <ecal/ecal.h>
#include <ecal/msg/protobuf/dynamic_subscriber.h>
#include <ecal/msg/protobuf/subscriber.h>

#include <memory>
#include <mutex>

#include <QtWidgets/QLabel>

#include "ui_plugin_widget.h"

#include "compressed_image.pb.h"

class PluginWidget : public QWidget, public eCAL::mon::PluginWidgetInterface
{
  Q_OBJECT
public:
  PluginWidget(const QString& topic_name, const QString& topic_type, QWidget* parent = Q_NULLPTR);
  virtual ~PluginWidget();

  virtual QWidget* getWidget();

public slots:
  virtual void onUpdate();

  virtual void onResume();
  virtual void onPause();

protected:
  Ui::PluginWidget ui_;

private slots:
  void updateContent();

private:
  eCAL::protobuf::CSubscriber<foxglove::CompressedImage> compressed_image_subscriber_;

  std::mutex                         proto_message_mutex_;
  foxglove::CompressedImage*         last_received_photo_;
  eCAL::Time::ecal_clock::time_point last_message_publish_timestamp_;

  QString                            topic_name_, topic_type_;
  bool                               new_msg_available_;
  int                                received_message_counter_;

  void photoReceivedMessageCallback(const foxglove::CompressedImage& message, long long send_time_usecs);
  void updatePublishTimeLabel();
};

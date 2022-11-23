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

#include <iostream>
#include <string>
#include <thread>

#include <QCameraInfo>
#include <QtWidgets>

#include "camera_wrapper.h"

CameraWrapper::CameraWrapper(
    eCAL::protobuf::CPublisher<foxglove::CompressedImage> &publisher,
    std::string &cameraName, uint16_t width, uint16_t height)
    : publisher_(publisher), cameraName_(cameraName), width_(width),
      height_(height), photosTaken_(0) {
  const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
  if (cameras.isEmpty()) {
    std::cerr << "No available camera to use" << std::endl;
    return;
  }

  for (const QCameraInfo &cameraInfo : cameras) {
    if (cameraInfo.deviceName().toStdString() == cameraName_) {
      setCamera(cameraInfo);
      return;
    }
  }

  std::cout << "Selected camera not found, setting to default camera."
            << std::endl;
  setCamera(QCameraInfo::defaultCamera());
}

CameraWrapper::~CameraWrapper() {}

void CameraWrapper::setCamera(const QCameraInfo &cameraInfo) {
  camera_.reset(new QCamera(cameraInfo));
  camera_.data()->setCaptureMode(QCamera::CaptureStillImage);
  camera_.data()->load();

  imageCapture_.reset(new QCameraImageCapture(camera_.data()));
  imageCapture_.data()->setCaptureDestination(
      QCameraImageCapture::CaptureToBuffer);

  if (isGivenResolutionSupported()) {
    QImageEncoderSettings imageSettings;
    imageSettings.setCodec("image/jpg");
    imageSettings.setResolution(width_, height_);
    imageCapture_.data()->setEncodingSettings(imageSettings);
  } else {
    std::cout << "Given resolution is not supported from the camera, setting "
                 "default resolution. List of supported resolutions: ";
    auto resolutions = imageCapture_.data()->supportedResolutions();
    for (const auto &it : resolutions) {
      std::cout << it.width() << "x" << it.height() << ", ";
    }
    std::cout << std::endl;
  }

  // connect
  QObject::connect(imageCapture_.data(), &QCameraImageCapture::imageCaptured,
                   [=](int id, QImage img) {
                     ++photosTaken_;
                     QByteArray buf;
                     QBuffer buffer(&buf);
                     buffer.open(QIODevice::WriteOnly);
                     img.save(&buffer, "JPG");
                     std::string protoData(buf.constData(), buf.length());
                     buffer.close();

                     // create and send protobuf
                     foxglove::CompressedImage compressedImageProto;
                     compressedImageProto.set_data(protoData);
                     compressedImageProto.set_format("jpg");
                     publisher_.Send(compressedImageProto);
#ifdef DEBUG
                     std::cout << "Sent photo number: " << photosTaken_
                               << " with size: "
                               << compressedImageProto.ByteSizeLong()
                               << std::endl;
#endif
                     emit photoSentSignal();
                   });

  QObject::connect(imageCapture_.data(),
                   &QCameraImageCapture::readyForCaptureChanged,
                   [=](bool state) {
                     if (state == true) {
                       capture();
                     }
                   });

  QObject::connect(this, &CameraWrapper::photoSentSignal, [this]() {
    if (isReadyForCapture()) {
      capture();
    }
  });

  for (const auto &frameRateRange :
       camera_.data()->supportedViewfinderFrameRateRanges()) {
    qDebug() << frameRateRange.minimumFrameRate << ", "
             << frameRateRange.maximumFrameRate;
  }

  camera_.data()->start();
}

void CameraWrapper::printAvailableCameras() {
  const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
  if (cameras.isEmpty()) {
    std::cout << "No available camera to use" << std::endl;
    return;
  }

  std::cout << "Available cameras: " << std::endl;

  for (const QCameraInfo &cameraInfo : cameras) {
    std::cout << "  " << cameraInfo.deviceName().toStdString() << std::endl;
  }
}

void CameraWrapper::capture() {
  camera_.data()->searchAndLock();
  imageCapture_.data()->capture();
  camera_.data()->unlock();
}

bool CameraWrapper::isGivenResolutionSupported() {
  QList<QSize> resolutions = imageCapture_.data()->supportedResolutions();
  QSize givenResolution(width_, height_);

  return resolutions.contains(givenResolution);
}

bool CameraWrapper::isReadyForCapture() {
  return imageCapture_.data()->isReadyForCapture();
}

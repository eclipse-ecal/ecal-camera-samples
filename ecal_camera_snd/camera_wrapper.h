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

#include <QCamera>
#include <QCameraImageCapture>
#include <QObject>
#include <QScopedPointer>

#include <ecal/msg/protobuf/publisher.h>

#include "compressed_image.pb.h"

class CameraWrapper : public QObject {
  Q_OBJECT
public:
  CameraWrapper(
      eCAL::protobuf::CPublisher<foxglove::CompressedImage> &publisher,
      std::string &camera_name, uint16_t width, uint16_t height);
  ~CameraWrapper();
  bool isReadyForCapture();

  void printAvailableCameras();

protected:
  virtual void capture();

private slots:
  void setCamera(const QCameraInfo &cameraInfo);

private:
  bool isGivenResolutionSupported();
  std::string supportedResolutionsList();

  QScopedPointer<QCamera> camera_;
  QScopedPointer<QCameraImageCapture> imageCapture_;

  eCAL::protobuf::CPublisher<foxglove::CompressedImage> &publisher_;

  std::string cameraName_;
  uint16_t width_;
  uint16_t height_;
  size_t photosTaken_;

signals:
  void photoSentSignal();
};

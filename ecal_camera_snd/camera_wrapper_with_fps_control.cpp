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

#include "camera_wrapper_with_fps_control.h"

#include <QDateTime>
#include <thread>

CameraWrapperWithFpsControl::CameraWrapperWithFpsControl(
    eCAL::protobuf::CPublisher<foxglove::CompressedImage> &publisher,
    std::string &camera_name, uint16_t width, uint16_t height, uint16_t maxFps)
    : CameraWrapper(publisher, camera_name, width, height),
      frameIntervalInMs(1000 / maxFps),
      lastFrameTimestamp(QDateTime::currentMSecsSinceEpoch()) {}

CameraWrapperWithFpsControl::~CameraWrapperWithFpsControl() {}

void CameraWrapperWithFpsControl::capture() {
  qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
  #ifdef DEBUG
  std::cout << "Time: " << currentTime << std::endl;
  #endif
  // limit the number of photos captured
  qint64 sleepingTime =
      currentTime - lastFrameTimestamp < frameIntervalInMs
          ? frameIntervalInMs - (currentTime - lastFrameTimestamp)
          : 0;

  std::this_thread::sleep_for(std::chrono::milliseconds(sleepingTime));

  CameraWrapper::capture();

  lastFrameTimestamp = QDateTime::currentMSecsSinceEpoch();
}

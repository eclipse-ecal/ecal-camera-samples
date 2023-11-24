# ========================= eCAL LICENSE =================================
#
# Copyright (C) 2016 - 2023 Continental Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#      http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# ========================= eCAL LICENSE =================================

import argparse
import os
import sys
# import the opencv library
import cv2
import ecal.core.core as ecal_core
from ecal.core.publisher import ProtoPublisher

import time

import ros.sensor_msgs.CompressedImage_pb2  as CompressedImage
import ros.sensor_msgs.Image_pb2 as RawImage

class CompressedImageHandler():
  
  def __init__(self, topic_name):
    self.pub = ProtoPublisher(topic_name, CompressedImage.CompressedImage)  
    self.image = CompressedImage.CompressedImage()

  def publish(self, video_frame):
    t = time.time()
    self.image.header.stamp.sec = int(t)
    self.image.header.stamp.nsec = 0
    self.image.data = cv2.imencode('.jpg', video_frame)[1].tobytes()
    self.image.format = "JPG"
    self.pub.send(self.image)
  

class RawImageHandler():
  def __init__(self, topic_name):
    self.pub = ProtoPublisher(topic_name, RawImage.Image)
    self.image = RawImage.Image()

  def publish(self, video_frame):
    t = time.time()
    self.image.header.stamp.sec = int(t)
    self.image.header.stamp.nsec = 0
    self.image.height = video_frame.shape[0]
    self.image.width = video_frame.shape[1]
    self.image.encoding = "bgr8"
    self.image.data = video_frame.tobytes()
    self.image.step = 3 * video_frame.shape[1]
    self.pub.send(self.image)

def main(args):
  # print eCAL version and date
  print("eCAL {} ({})\n".format(ecal_core.getversion(), ecal_core.getdate()))
  
  # initialize eCAL API
  ecal_core.initialize(sys.argv, "py_webcam_grabber")

  if (args.compressed):
    Handler = CompressedImageHandler
  else:
    Handler = RawImageHandler

  handler = Handler(args.topic_name)

  # define a video capture object
  vid = cv2.VideoCapture(args.camera_id)
  if (vid.isOpened() == False):
    print("Unable to read camera feed")

  # send messages
  while ecal_core.ok():
    ret, frame = vid.read()
    if ret:
      handler.publish(frame)
      # sleep 100 ms
      time.sleep(0.1)
  
  # finalize eCAL API
  vid.release()
  ecal_core.finalize()


def create_parser():
  parser = argparse.ArgumentParser()
  parser.add_argument("--camera-id", dest="camera_id", type=int, default=0, help="Which camera to use for feed")
  parser.add_argument("--compressed", help="send compressed image instead of raw image", action="store_true")
  parser.add_argument("--topic-name", dest="topic_name", help="topic name to publish", default='Webcam')
  return parser

if __name__ == "__main__":
  parser = create_parser()
  args = parser.parse_args()
  main(args)  
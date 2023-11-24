# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ros/nav_msgs/Odometry.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from ros.geometry_msgs import PoseWithCovariance_pb2 as ros_dot_geometry__msgs_dot_PoseWithCovariance__pb2
from ros.geometry_msgs import TwistWithCovariance_pb2 as ros_dot_geometry__msgs_dot_TwistWithCovariance__pb2
from ros.std_msgs import Header_pb2 as ros_dot_std__msgs_dot_Header__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1bros/nav_msgs/Odometry.proto\x12\x0cros.nav_msgs\x1a*ros/geometry_msgs/PoseWithCovariance.proto\x1a+ros/geometry_msgs/TwistWithCovariance.proto\x1a\x19ros/std_msgs/Header.proto\"\xb4\x01\n\x08Odometry\x12$\n\x06header\x18\x01 \x01(\x0b\x32\x14.ros.std_msgs.Header\x12\x16\n\x0e\x63hild_frame_id\x18\x02 \x01(\t\x12\x33\n\x04pose\x18\x03 \x01(\x0b\x32%.ros.geometry_msgs.PoseWithCovariance\x12\x35\n\x05twist\x18\x04 \x01(\x0b\x32&.ros.geometry_msgs.TwistWithCovarianceb\x06proto3')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'ros.nav_msgs.Odometry_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _ODOMETRY._serialized_start=162
  _ODOMETRY._serialized_end=342
# @@protoc_insertion_point(module_scope)
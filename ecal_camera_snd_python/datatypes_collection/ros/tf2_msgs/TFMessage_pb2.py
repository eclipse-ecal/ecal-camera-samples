# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ros/tf2_msgs/TFMessage.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from ros.geometry_msgs import TransformStamped_pb2 as ros_dot_geometry__msgs_dot_TransformStamped__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1cros/tf2_msgs/TFMessage.proto\x12\x0cros.tf2_msgs\x1a(ros/geometry_msgs/TransformStamped.proto\"D\n\tTFMessage\x12\x37\n\ntransforms\x18\x01 \x03(\x0b\x32#.ros.geometry_msgs.TransformStampedb\x06proto3')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'ros.tf2_msgs.TFMessage_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _TFMESSAGE._serialized_start=88
  _TFMESSAGE._serialized_end=156
# @@protoc_insertion_point(module_scope)

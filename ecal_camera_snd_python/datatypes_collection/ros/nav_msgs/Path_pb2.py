# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ros/nav_msgs/Path.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from ros.geometry_msgs import PoseStamped_pb2 as ros_dot_geometry__msgs_dot_PoseStamped__pb2
from ros.std_msgs import Header_pb2 as ros_dot_std__msgs_dot_Header__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x17ros/nav_msgs/Path.proto\x12\x0cros.nav_msgs\x1a#ros/geometry_msgs/PoseStamped.proto\x1a\x19ros/std_msgs/Header.proto\"[\n\x04Path\x12$\n\x06header\x18\x01 \x01(\x0b\x32\x14.ros.std_msgs.Header\x12-\n\x05poses\x18\x02 \x03(\x0b\x32\x1e.ros.geometry_msgs.PoseStampedb\x06proto3')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'ros.nav_msgs.Path_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _PATH._serialized_start=105
  _PATH._serialized_end=196
# @@protoc_insertion_point(module_scope)
# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ros/sensor_msgs/Range.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from ros.std_msgs import Header_pb2 as ros_dot_std__msgs_dot_Header__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1bros/sensor_msgs/Range.proto\x12\x0fros.sensor_msgs\x1a\x19ros/std_msgs/Header.proto\"\x91\x01\n\x05Range\x12$\n\x06header\x18\x01 \x01(\x0b\x32\x14.ros.std_msgs.Header\x12\x16\n\x0eradiation_type\x18\x02 \x01(\x05\x12\x15\n\rfield_of_view\x18\x03 \x01(\x02\x12\x11\n\tmin_range\x18\x04 \x01(\x02\x12\x11\n\tmax_range\x18\x05 \x01(\x02\x12\r\n\x05range\x18\x06 \x01(\x02\x62\x06proto3')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'ros.sensor_msgs.Range_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _RANGE._serialized_start=76
  _RANGE._serialized_end=221
# @@protoc_insertion_point(module_scope)

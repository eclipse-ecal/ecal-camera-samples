# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ros/diagnostic_msgs/DiagnosticArray.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from ros.diagnostic_msgs import DiagnosticStatus_pb2 as ros_dot_diagnostic__msgs_dot_DiagnosticStatus__pb2
from ros.std_msgs import Header_pb2 as ros_dot_std__msgs_dot_Header__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n)ros/diagnostic_msgs/DiagnosticArray.proto\x12\x13ros.diagnostic_msgs\x1a*ros/diagnostic_msgs/DiagnosticStatus.proto\x1a\x19ros/std_msgs/Header.proto\"n\n\x0f\x44iagnosticArray\x12$\n\x06header\x18\x01 \x01(\x0b\x32\x14.ros.std_msgs.Header\x12\x35\n\x06status\x18\x02 \x03(\x0b\x32%.ros.diagnostic_msgs.DiagnosticStatusb\x06proto3')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'ros.diagnostic_msgs.DiagnosticArray_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _DIAGNOSTICARRAY._serialized_start=137
  _DIAGNOSTICARRAY._serialized_end=247
# @@protoc_insertion_point(module_scope)
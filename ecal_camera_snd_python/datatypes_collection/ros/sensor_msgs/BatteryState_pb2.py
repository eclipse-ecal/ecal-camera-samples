# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ros/sensor_msgs/BatteryState.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from ros.std_msgs import Header_pb2 as ros_dot_std__msgs_dot_Header__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\"ros/sensor_msgs/BatteryState.proto\x12\x0fros.sensor_msgs\x1a\x19ros/std_msgs/Header.proto\"\xff\x02\n\x0c\x42\x61tteryState\x12$\n\x06header\x18\x01 \x01(\x0b\x32\x14.ros.std_msgs.Header\x12\x0f\n\x07voltage\x18\x02 \x01(\x02\x12\x13\n\x0btemperature\x18\x03 \x01(\x02\x12\x0f\n\x07\x63urrent\x18\x04 \x01(\x02\x12\x0e\n\x06\x63harge\x18\x05 \x01(\x02\x12\x10\n\x08\x63\x61pacity\x18\x06 \x01(\x02\x12\x17\n\x0f\x64\x65sign_capacity\x18\x07 \x01(\x02\x12\x12\n\npercentage\x18\x08 \x01(\x02\x12\x1b\n\x13power_supply_status\x18\t \x01(\x05\x12\x1b\n\x13power_supply_health\x18\n \x01(\x05\x12\x1f\n\x17power_supply_technology\x18\x0b \x01(\x05\x12\x0f\n\x07present\x18\x0c \x01(\x08\x12\x14\n\x0c\x63\x65ll_voltage\x18\r \x03(\x02\x12\x18\n\x10\x63\x65ll_temperature\x18\x0e \x03(\x02\x12\x10\n\x08location\x18\x0f \x01(\t\x12\x15\n\rserial_number\x18\x10 \x01(\tb\x06proto3')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'ros.sensor_msgs.BatteryState_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _BATTERYSTATE._serialized_start=83
  _BATTERYSTATE._serialized_end=466
# @@protoc_insertion_point(module_scope)

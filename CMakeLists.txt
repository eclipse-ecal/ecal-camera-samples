# ========================= LICENSE =================================
#
# Copyright (C) 2022 Continental Corporation
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
# ========================= LICENSE =================================

cmake_minimum_required(VERSION 3.4)
project(ecal-camera-samples)

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_NAME})

set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})
set(CPACK_PACKAGE_CONTACT "mirza.canovic@gmail.com")
set(CPACK_OUTPUT_FILE_PREFIX _deploy)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

add_definitions(-DQWT_DLL)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(UNIX)
 set(CMAKE_LINK_WHAT_YOU_USE ON)
endif(UNIX)
# Set CMake policy behavior (alias targets)
cmake_policy(SET CMP0028 NEW)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0057 NEW)
cmake_policy(SET CMP0054 NEW)
cmake_policy(SET CMP0080 NEW)

# --------------------------------------------------------
# set ECAL_MON_PLUGIN_DIR install dir
# --------------------------------------------------------
include(GNUInstallDirs)
if(WIN32)
  set(ECAL_MON_PLUGIN_DIR ecalmon_plugins)
else()
  set(ECAL_MON_PLUGIN_DIR ecal/plugins/mon)
endif()

set(eCAL_install_lib_dir  ${CMAKE_INSTALL_LIBDIR})
set(eCAL_install_bin_dir  ${CMAKE_INSTALL_BINDIR})

if (WIN32)
   if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set(PLATFORM_NAME "x64")
   else()
    set(PLATFORM_NAME "win32")
  endif()
  set(VS_PLATFORM "v140_${PLATFORM_NAME}")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_utils/mon_functions.cmake)

# --------------------------------------------------------
# command line build options
# use it that way cmake .. -DHAS_OPENCV=ON
# --------------------------------------------------------
include(CMakeDependentOption)

# --------------------------------------------------------
# detect qt library
# --------------------------------------------------------
if(WIN32)
  if(NOT DEFINED ENV{QT5_ROOT_DIRECTORY})
    # If the QT5_ROOT_DIRECTORY Variable is not set, there is still a chance that 
    # the user set the CMAKE_PREFIX_PATH himself. Thus we try to find
    # Qt5 Core just to see if that works. If we can find Qt, we assume
    # that the user knows what he is doing.
    find_package(Qt5 COMPONENTS Core)
    if (NOT Qt5_FOUND)
      message(FATAL_ERROR "QT5_ROOT_DIRECTORY is not defined. Please create an \
        environment variable QT5_ROOT_DIRECTORY pointing to your QT5 installation \
        (the directory that contains the msvc2015 or msvc2015_64 \
        directory)")
    endif()
  else()
    if(NOT CMAKE_CL_64)
      # Add 32bit Qt5
      list(APPEND CMAKE_PREFIX_PATH $ENV{QT5_ROOT_DIRECTORY}/msvc2015/)
      message(STATUS "QT 32 Bit")
      message(STATUS "CMAKE_PREFIX_PATH appended: $ENV{QT5_ROOT_DIRECTORY}/msvc2015/")
    else ()
      # Add 64bit Qt5
      list(APPEND CMAKE_PREFIX_PATH $ENV{QT5_ROOT_DIRECTORY}/msvc2015_64/)
      message(STATUS "QT 64 Bit")
      message(STATUS "CMAKE_PREFIX_PATH appended: $ENV{QT5_ROOT_DIRECTORY}/msvc2015_64/")
    endif()
  endif()
endif(WIN32)

if(WIN32)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake_utils/qt/qt_windeployqt.cmake)
endif()


if(POLICY CMP0071)
  cmake_policy(SET CMP0071 NEW)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC OFF) # Reason for being turned off: AutoUIC will prevent VS from detecting changes in .ui files
set(CMAKE_AUTORCC OFF) # Reason for being turned off: AutoRCC will create an entirely new project in VS which clutters the solution appearance. Additionally, we cannot assign a source group to the generated .cpp files which will clutter the project.
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(eCAL COMPONENTS core pb mon_plugin_lib  REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Protobuf REQUIRED)

create_targets_protobuf()
set(THREADS_PREFER_PTHREAD_FLAG ON)

if(UNIX)
  message(STATUS "GCC detected - Adding flags")
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
  add_definitions(-fno-pie -fno-PIE -fPIC)
  if(NOT CMAKE_VERSION VERSION_LESS 3.10 AND NOT OpenGL_GL_PREFERENCE)
    set(OpenGL_GL_PREFERENCE GLVND)
  endif()
endif()


add_subdirectory(ecal_camera_snd)
add_subdirectory(camera_receiver_mon_plugin)

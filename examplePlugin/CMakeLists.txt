# Copyright 2020 The Mumble Developers. All rights reserved.
# Use of this source code is governed by a BSD-style license
# that can be found in the LICENSE file at the root of the
# Mumble source tree or at <https://www.mumble.info/LICENSE>.

cmake_minimum_required(VERSION 3.12)

set(version "1.0.0")

project(ExamplePlugin
	VERSION "${version}"
	DESCRIPTION "An example plugin for Mumble using the C++ plugin wrapper"
	LANGUAGES "CXX"
)

# In order to use additional parts of the plugin interface, you have to enable the respective optiopn
# e.g. set(server-event-callbacks ON)

# We need the wrapper as a depency
add_subdirectory(.. "${CMAKE_CURRENT_BINARY_DIR}/wrapper")

# set_target_properties(mumble_plugin_cpp_wrapper PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

add_library(example SHARED
	plugin.cpp
	$<TARGET_OBJECTS:mumble_plugin_cpp_wrapper>
)

target_include_directories(example
	PRIVATE
		"../include"
)

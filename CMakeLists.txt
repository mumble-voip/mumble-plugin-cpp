# Copyright 2020 The Mumble Developers. All rights reserved.
# Use of this source code is governed by a BSD-style license
# that can be found in the LICENSE file at the root of the
# source tree.

cmake_minimum_required(VERSION 3.12)

set(version "1.0.0")

project(MumblePluginCppWrapper
	VERSION "${version}"
	DESCRIPTION "C++ wrapper of Mumble's C plugin API"
	LANGUAGES "CXX"
)

set(CMAKE_CXX_STANDARD 17)

option(positional-audio "Include functions for positional audio" OFF)
option(server-event-callbacks "Include callback functions for server-events" OFF)
option(audio-callbacks "Include callback audio functions" OFF)
option(plugin-data-callbacks "Include functions for receiving network messages from other plugins" OFF)
option(key-event-callbacks "Include callback functions for key-events" OFF)
option(plugin-update "Include functions for self-updating the plugin" OFF)

option(all-callbacks "Include event callback functions" OFF)
option(all-features "Shortcut for enabling all plugin features" OFF)

# Required in order to link code from this target to the final shared lib
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Build as an object library in order for the actual plugin lib to be able to include 
# it easily
add_library(mumble_plugin_cpp_wrapper OBJECT
	src/MumblePluginDefaultImpl.cpp
	src/MumbleAPI.cpp
	src/plugin.cpp
)

target_include_directories(mumble_plugin_cpp_wrapper
	PUBLIC
		"include"
)

if (positional-audio OR all-features)
	target_compile_definitions(mumble_plugin_cpp_wrapper
		PUBLIC
			"MUMBLE_PLUGIN_WRAPPER_USE_POSITIONAL_AUDIO"
	)
endif()

if (server-event-callbacks OR all-callbacks OR all-features)
	message(STATUS "test")
	target_compile_definitions(mumble_plugin_cpp_wrapper
		PUBLIC
			"MUMBLE_PLUGIN_WRAPPER_USE_SERVER_EVENT_CALLBACKS"
	)
endif()

if (audio-callbacks OR all-callbacks OR all-features)
	target_compile_definitions(mumble_plugin_cpp_wrapper
		PUBLIC
			"MUMBLE_PLUGIN_WRAPPER_USE_AUDIO_CALLBACKS"
	)
endif()

if (plugin-data-callbacks OR all-callbacks OR all-features)
	target_compile_definitions(mumble_plugin_cpp_wrapper
		PUBLIC
			"MUMBLE_PLUGIN_WRAPPER_USE_PLUGIN_DATA_FRAMEWORK_CALLBACKS"
	)
endif()

if (key-event-callbacks OR all-callbacks OR all-features)
	target_compile_definitions(mumble_plugin_cpp_wrapper
		PUBLIC
			"MUMBLE_PLUGIN_WRAPPER_USE_KEY_EVENT_CALLBACKS"
	)
endif()

if (plugin-update OR all-callbacks OR all-features)
	target_compile_definitions(mumble_plugin_cpp_wrapper
		PUBLIC
			"MUMBLE_PLUGIN_WRAPPER_USE_PLUGIN_UPDATES"
	)
endif()

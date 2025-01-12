# Copyright The Mumble Developers. All rights reserved.
# Use of this source code is governed by a BSD-style license
# that can be found in the LICENSE file at the root of the
# source tree.

cmake_minimum_required(VERSION 3.0...3.31)

set(version "1.1.0")

project(MumblePluginCppWrapper
	VERSION "${version}"
	DESCRIPTION "C++ wrapper of Mumble's C plugin API"
	LANGUAGES "CXX"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(positional-audio "Include functions for positional audio" OFF)
option(server-event-callbacks "Include callback functions for server-events" OFF)
option(audio-callbacks "Include callback audio functions" OFF)
option(plugin-data-callbacks "Include functions for receiving network messages from other plugins" OFF)
option(key-event-callbacks "Include callback functions for key-events" OFF)
option(plugin-update "Include functions for self-updating the plugin" OFF)

option(all-callbacks "Include event callback functions" OFF)
option(all-features "Shortcut for enabling all plugin features" OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(mumble_plugin_cpp_wrapper
	STATIC
		"src/MumblePluginDefaultImpl.cpp"
		"src/plugin.cpp"
)
add_library(mumble_plugin_cpp_wrapper_api
	STATIC
		"src/MumbleAPI.cpp"
)

target_include_directories(mumble_plugin_cpp_wrapper PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(mumble_plugin_cpp_wrapper_api PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_compile_definitions(mumble_plugin_cpp_wrapper_api
	PUBLIC
		MUMBLE_PLUGIN_NO_DEFAULT_FUNCTION_DEFINITIONS
		MUMBLE_PLUGIN_NO_API_TYPEDEF
)

target_link_libraries(mumble_plugin_cpp_wrapper PUBLIC mumble_plugin_cpp_wrapper_api)


if (server-event-callbacks OR all-callbacks OR all-features)
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

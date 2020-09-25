# Copyright 2020 The Mumble Developers. All rights reserved.
# Use of this source code is governed by a BSD-style license
# that can be found in the LICENSE file at the root of the
# Mumble source tree or at <https://www.mumble.info/LICENSE>.

cmake_minimum_required(VERSION 3.0)

set(version "1.0.0")

project(ExamplePlugin
	VERSION "${version}"
	DESCRIPTION "An example plugin for Mumble using the C++ plugin wrapper"
	LANGUAGES "CXX"
)

# Cpp17 or later is required in order to use the wrapper
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# In order to use additional parts of the plugin interface, you have to enable the respective optiopn
# e.g. set(positional-audio ON)
set(server-event-callbacks ON CACHE BOOL "" FORCE)

# We need the wrapper as a depency
add_subdirectory(.. "${CMAKE_CURRENT_BINARY_DIR}/wrapper")

add_library(example SHARED
	plugin.cpp
	# Add the object files from the wrapper-lib
	$<TARGET_OBJECTS:mumble_plugin_cpp_wrapper>
)

# The interface compile-definitons of the wrapper lib  and its include directories
# have to be copied manually as target_link_libraries doesn't work for object files
# (will result in linker error due to problems with symbol relocation).
get_target_property(NEEDED_COMPILE_DEFINITONS mumble_plugin_cpp_wrapper INTERFACE_COMPILE_DEFINITIONS)
target_compile_definitions(example
	PUBLIC
		${NEEDED_COMPILE_DEFINITONS}
)
get_target_property(NEEDED_INCLUDE_DIRS mumble_plugin_cpp_wrapper INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(example
	PUBLIC
		${NEEDED_INCLUDE_DIRS}
)

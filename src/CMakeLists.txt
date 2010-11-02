cmake_minimum_required(VERSION 2.6)
project(computational)

include_directories(${ROOT_INCLUDES})

SET(ROOTSYS "/usr/")
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(LIBS z m gobject-2.0 sigc-2.0 stdc++  ccext2 ccgnu2 dl rt )

set (LIBXMLFLAGS )
set (LIBCPP2FLAGS ccext2 ccgnu2 dl)

FIND_PACKAGE(ROOT)
if(NOT ROOT_FOUND)
	MESSAGE("Could not find ROOT installation.")
endif(NOT ROOT_FOUND)

add_subdirectory(0randwalk)
add_subdirectory(1standnorm)
add_subdirectory(2standnormroot)

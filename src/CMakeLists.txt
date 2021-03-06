cmake_minimum_required(VERSION 2.6)
project(computational)

include_directories(${ROOT_INCLUDES})

SET(ENV{ROOTSYS} "/usr/")
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(LIBS z m gobject-2.0 sigc-2.0 stdc++  ccext2 ccgnu2 dl rt )

set (LIBXMLFLAGS )
set (LIBCPP2FLAGS ccext2 ccgnu2 dl)

FIND_PACKAGE(ROOT)
if(NOT ROOT_FOUND)
	MESSAGE("Could not find ROOT installation.")
endif(NOT ROOT_FOUND)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-msse3 -march=core2 -O2 -pipe")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-msse3 -march=core2 -O2 -pipe")

#set_target_properties(xymodelsdl PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

add_subdirectory(0randwalk)
add_subdirectory(1standnorm)
add_subdirectory(2standnormroot)
add_subdirectory(3randuroot)
add_subdirectory(4boxmullerroot)
add_subdirectory(5polarroot)
add_subdirectory(6badlcgpolar)
add_subdirectory(7normalaccrej)
add_subdirectory(8monteintegr)
add_subdirectory(9impsampling)
add_subdirectory(10impddim)
add_subdirectory(11isingsann)
add_subdirectory(12markchain)
add_subdirectory(13slicesample)
add_subdirectory(14sstruncnorm)
add_subdirectory(15xymodelsdl)
add_subdirectory(GL)

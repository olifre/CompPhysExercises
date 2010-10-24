cmake_minimum_required(VERSION 2.6)
project(computational)

set(LIBS z m gobject-2.0 sigc-2.0 stdc++  ccext2 ccgnu2 dl rt )

set (LIBXMLFLAGS )
set (LIBCPP2FLAGS ccext2 ccgnu2 dl)

add_subdirectory(0randwalk)
add_subdirectory(1standnorm)

add_executable(sdlising WIN32 MACOSX_BUNDLE sdlising.cpp)

target_link_libraries(sdlising SDL tcmalloc profiler)

#set_target_properties(sdlising PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

install(TARGETS sdlising DESTINATION bin)

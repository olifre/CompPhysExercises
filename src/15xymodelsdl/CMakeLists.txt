add_executable(xymodelsdl WIN32 MACOSX_BUNDLE xymodelsdl.cpp)

target_link_libraries(xymodelsdl SDL tcmalloc profiler)

#set_target_properties(xymodelsdl PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

install(TARGETS xymodelsdl DESTINATION bin)

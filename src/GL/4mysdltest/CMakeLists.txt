add_executable(mysdltest mysdltest.cpp)

target_link_libraries(mysdltest SDL)

install(TARGETS mysdltest DESTINATION bin)

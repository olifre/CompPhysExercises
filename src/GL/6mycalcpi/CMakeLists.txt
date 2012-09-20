add_executable(mycalcpi mycalcpi.cpp)

target_link_libraries(mycalcpi)

#set_target_properties(mycalcpi)

install(TARGETS mycalcpi DESTINATION bin)

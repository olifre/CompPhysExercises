add_executable(mygldemo mygldemo.cpp)

target_link_libraries(mygldemo GL GLU glut)

install(TARGETS mygldemo DESTINATION bin)

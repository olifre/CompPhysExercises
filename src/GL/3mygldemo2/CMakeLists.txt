add_executable(mygldemo2 mygldemo2.cpp)

target_link_libraries(mygldemo2 GL GLU glut)

install(TARGETS mygldemo2 DESTINATION bin)

find_package(Qt4 REQUIRED) # find and setup Qt4 for this project

add_executable(myqttest myqttest.cpp)

target_link_libraries(myqttest GL GLU glut)

install(TARGETS myqttest DESTINATION bin)

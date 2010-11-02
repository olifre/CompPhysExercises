include_directories(${ROOT_INCLUDES})
add_executable(standnormroot standnormroot.cpp)

target_link_libraries(standnormroot -L${ROOT_LIBRARY_DIR} Core Cint RIO Net Hist Tree MathCore Thread Physics Matrix)

install(TARGETS standnormroot DESTINATION bin)

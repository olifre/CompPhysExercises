include_directories(${ROOT_INCLUDES})
add_executable(polarroot polarroot.cpp)

target_link_libraries(polarroot -L${ROOT_LIBRARY_DIR} Core Cint RIO Net Hist Tree MathCore Thread Physics Matrix)

install(TARGETS polarroot DESTINATION bin)

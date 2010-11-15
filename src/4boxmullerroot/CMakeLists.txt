include_directories(${ROOT_INCLUDES})
add_executable(boxmullerroot boxmullerroot.cpp)

target_link_libraries(boxmullerroot -L${ROOT_LIBRARY_DIR} Core Cint RIO Net Hist Tree MathCore Thread Physics Matrix)

install(TARGETS boxmullerroot DESTINATION bin)

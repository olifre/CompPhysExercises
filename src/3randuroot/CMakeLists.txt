include_directories(${ROOT_INCLUDES})
add_executable(randuroot randuroot.cpp)

target_link_libraries(randuroot -L${ROOT_LIBRARY_DIR} Core Cint RIO Net Hist Tree MathCore Thread Physics Matrix)

install(TARGETS randuroot DESTINATION bin)

include_directories(${ROOT_INCLUDES})
add_executable(normalaccrej normalaccrej.cpp)

target_link_libraries(normalaccrej -L${ROOT_LIBRARY_DIR} Core Cint RIO Net Hist Tree MathCore Thread Physics Matrix)

install(TARGETS normalaccrej DESTINATION bin)

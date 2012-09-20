add_executable(markchain markchain.cpp)
include_directories(${ROOT_INCLUDES})

target_link_libraries(markchain -L${ROOT_LIBRARY_DIR} Core Cint RIO Net Hist Tree MathCore Thread Physics Matrix)

install(TARGETS markchain DESTINATION bin)

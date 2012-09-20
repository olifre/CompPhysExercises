add_executable(slicesample slicesample.cpp)
include_directories(${ROOT_INCLUDES})

target_link_libraries(slicesample -L${ROOT_LIBRARY_DIR} Core Cint RIO Net Hist Tree MathCore Thread Physics Matrix)

install(TARGETS slicesample DESTINATION bin)

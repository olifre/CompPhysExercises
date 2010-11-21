include_directories(${ROOT_INCLUDES})
add_executable(badlcgpolar badlcgpolar.cpp)

target_link_libraries(badlcgpolar -L${ROOT_LIBRARY_DIR} Core Cint RIO Net Hist Tree MathCore Thread Physics Matrix)

install(TARGETS badlcgpolar DESTINATION bin)

add_executable(sstruncnorm sstruncnorm.cpp)
include_directories(${ROOT_INCLUDES})

target_link_libraries(sstruncnorm -L${ROOT_LIBRARY_DIR} Core Cint RIO Net Hist Tree MathCore Thread Physics Matrix)

install(TARGETS sstruncnorm DESTINATION bin)

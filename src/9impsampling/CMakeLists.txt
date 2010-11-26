add_executable(impsampling impsampling.cpp)

target_link_libraries(impsampling)

install(TARGETS impsampling DESTINATION bin)

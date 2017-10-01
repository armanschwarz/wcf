add_executable(libTest main.cpp test.cpp)

target_link_libraries(libTest ${Boost_LIBRARIES} lib)

add_test(libTest libTest)

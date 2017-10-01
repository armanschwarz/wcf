add_library(lib tools.cpp buildVariablesMap.cpp)

target_link_libraries(lib ${Boost_LIBRARIES})

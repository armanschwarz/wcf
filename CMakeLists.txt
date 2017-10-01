cmake_minimum_required(VERSION 3.0)

add_definitions(-std=c++14 -Wpedantic -Wall -Wextra)

find_package(Boost 1.60.0 COMPONENTS
    program_options
    unit_test_framework
    filesystem
    system
    REQUIRED)

enable_testing()

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(test)

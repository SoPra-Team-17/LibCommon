cmake_minimum_required(VERSION 3.10)

find_package(nlohmann_json REQUIRED)

include_directories(../src)
include_directories(../src/datatypes)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif ()

add_executable(allTests gadgetTest.cpp jsonEncodingTest.cpp jsonDecodingTest.cpp characterTest.cpp)
target_link_libraries(allTests gtest gmock gtest_main SopraCommon nlohmann_json::nlohmann_json)
gtest_discover_tests(allTests)

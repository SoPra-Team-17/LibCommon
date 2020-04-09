cmake_minimum_required(VERSION 3.10)

find_package(nlohmann_json REQUIRED)

include_directories(../src)
include_directories(../src/datatypes)

set(SOURCES
        gadgetTest.cpp
        jsonEncodingTest.cpp
        jsonDecodingTest.cpp
        characterTest.cpp
        matchConfigTest.cpp
        pointTest.cpp
        messages/helloMessageTest.cpp
        util/uuidTest.cpp)

add_executable(allTests ${SOURCES})

target_link_libraries(allTests gtest gmock gtest_main SopraCommon nlohmann_json::nlohmann_json)
gtest_discover_tests(allTests)

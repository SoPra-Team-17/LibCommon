cmake_minimum_required(VERSION 3.10)

find_package(nlohmann_json REQUIRED)

include_directories(../src)
include_directories(../src/datatypes)

set(SOURCES
        datatypes/gadgetTest.cpp
        datatypes/jsonEncodingTest.cpp
        datatypes/jsonDecodingTest.cpp
        datatypes/characterTest.cpp
        datatypes/matchConfigTest.cpp
        datatypes/scenarioTest.cpp
        util/pointTest.cpp
        util/uuidTest.cpp
        util/optionalSerialization.cpp)

add_executable(allTests ${SOURCES})

target_link_libraries(allTests gtest gmock gtest_main SopraCommon nlohmann_json::nlohmann_json)
gtest_discover_tests(allTests)

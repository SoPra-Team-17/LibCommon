cmake_minimum_required(VERSION 3.10)

find_package(nlohmann_json REQUIRED)

include_directories(../src)
include_directories(../src/datatypes)

set(SOURCES
        datatypes/gadgetTest.cpp
        datatypes/jsonEncodingTest.cpp
        datatypes/jsonDecodingTest.cpp
        datatypes/characterSetTest.cpp
        datatypes/characterTest.cpp
        datatypes/matchConfigTest.cpp
        datatypes/scenarioTest.cpp
        gameplay/exfiltrationTest.cpp
        gameplay/gadgetActionTest.cpp
        gameplay/gambleActionTest.cpp
        gameplay/movementActionTest.cpp
        gameplay/propertyActionTest.cpp
        util/pointTest.cpp
        util/uuidTest.cpp
        util/optionalSerialization.cpp
        messages/helloMessageTest.cpp
        messages/itemChoiceMessageTest.cpp
        messages/metaInformationTest.cpp
        messages/messageEncodeDecode.cpp
        messages/debugInfoTest.cpp
        gameLogic/lineOfSightTests.cpp)

add_executable(allTests ${SOURCES})
target_compile_options(allTests PRIVATE ${COMMON_CXX_FLAGS})
target_link_libraries(allTests
        gtest
        gmock
        gtest_main
        SopraCommon
        nlohmann_json::nlohmann_json
        $<$<CONFIG:Debug>:--coverage>)
gtest_discover_tests(allTests)

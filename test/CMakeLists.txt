cmake_minimum_required(VERSION 3.10)

find_package(nlohmann_json REQUIRED)

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
        messages/messageValidateTest.cpp
        messages/equipmentChoiceTest.cpp
        gameLogic/lineOfSightTests.cpp
        gameLogic/movementTests.cpp
        gameLogic/gadget/hairdryerTests.cpp
        gameLogic/gadget/technicolourPrismTests.cpp
        gameLogic/gadget/cocktailTests.cpp
        gameLogic/gadget/chickenFeedTests.cpp
        gameLogic/gadget/jetpackTests.cpp
        gameLogic/gadget/gasGlossTests.cpp
        gameLogic/gadget/poisonPillTests.cpp
        gameLogic/gadget/nuggetTests.cpp
        gameLogic/gadget/wiretapWithEarplugsTests.cpp
        gameLogic/gadget/diamondCollarTests.cpp
        gameLogic/retireTests.cpp)

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

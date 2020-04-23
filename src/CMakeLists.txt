cmake_minimum_required(VERSION 3.10)
project(SopraCommon)

find_package(nlohmann_json REQUIRED)

set(SOURCE
        datatypes/gadgets/Gadget.cpp
        datatypes/gadgets/WiretapWithEarplugs.cpp
        datatypes/gadgets/Cocktail.cpp
        datatypes/gameplay/Exfiltration.cpp
        datatypes/gameplay/GadgetAction.cpp
        datatypes/gameplay/GambleAction.cpp
        datatypes/gameplay/Movement.cpp
        datatypes/gameplay/Operation.cpp
        datatypes/gameplay/PropertyAction.cpp
        datatypes/character/Character.cpp
        datatypes/character/CharacterInformation.cpp
        datatypes/character/CharacterDescription.cpp
        datatypes/matchconfig/MatchConfig.cpp
        datatypes/scenario/Scenario.cpp
        datatypes/scenario/Scenario.cpp
        datatypes/scenario/FieldMap.cpp
        datatypes/scenario/Field.cpp
        datatypes/statistics/StatisticsEntry.cpp
        datatypes/statistics/Statistics.cpp
        datatypes/gameplay/State.cpp
        network/messages/EquipmentChoice.cpp
        network/messages/Error.cpp
        network/messages/GameLeave.cpp
        network/messages/GameLeft.cpp
        network/messages/GameOperation.cpp
        network/messages/GamePause.cpp
        network/messages/Hello.cpp
        network/messages/HelloReply.cpp
        network/MessageContainer.cpp
        util/UUID.cpp
        util/Point.cpp
        network/messages/GameStarted.cpp
        network/messages/Reconnect.cpp
        network/messages/RequestItemChoice.cpp
        network/messages/ItemChoice.cpp
        network/messages/MetaInformation.cpp
        network/messages/RequestEquipmentChoice.cpp
        network/messages/RequestGameOperation.cpp
        network/messages/GameStatus.cpp
        network/messages/RequestGamePause.cpp
        network/messages/RequestMetaInformation.cpp
        network/messages/Strike.cpp
        network/messages/RequestReplay.cpp
        network/messages/Replay.cpp
        network/messages/StatisticsMessage.cpp)

set(HEADER
        datatypes/character/PropertyEnum.hpp
        datatypes/gadgets/GadgetEnum.hpp
        datatypes/gameplay/OperationEnum.hpp
        datatypes/scenario/FieldStateEnum.hpp
        datatypes/statistics/VictoryEnum.hpp
        network/RoleEnum.hpp
        network/messages/MessageTypeEnum.hpp
        util/OptionalSerialization.hpp
        util/VariantSerialization.hpp
        datatypes/gadgets/Gadget.hpp
        datatypes/gadgets/WiretapWithEarplugs.hpp
        datatypes/gadgets/Cocktail.hpp
        datatypes/gameplay/Exfiltration.hpp
        datatypes/gameplay/GadgetAction.hpp
        datatypes/gameplay/GambleAction.hpp
        datatypes/gameplay/Movement.hpp
        datatypes/gameplay/Operation.hpp
        datatypes/gameplay/PropertyAction.hpp
        datatypes/character/Character.hpp
        datatypes/character/CharacterInformation.hpp
        datatypes/character/CharacterDescription.hpp
        datatypes/matchconfig/MatchConfig.hpp
        datatypes/scenario/Scenario.hpp
        datatypes/scenario/Scenario.hpp
        datatypes/scenario/FieldMap.hpp
        datatypes/scenario/Field.hpp
        datatypes/statistics/StatisticsEntry.hpp
        datatypes/statistics/Statistics.hpp
        datatypes/gameplay/State.hpp
        network/messages/EquipmentChoice.hpp
        network/messages/Error.hpp
        network/messages/GameLeave.hpp
        network/messages/GameLeft.hpp
        network/messages/GameOperation.hpp
        network/messages/GamePause.hpp
        network/messages/Hello.hpp
        network/messages/HelloReply.hpp
        network/MessageContainer.hpp
        util/UUID.hpp
        util/Point.hpp
        network/messages/GameStarted.hpp
        network/messages/Reconnect.hpp
        network/messages/RequestItemChoice.hpp
        network/messages/ItemChoice.hpp
        network/messages/MetaInformation.hpp
        network/messages/RequestEquipmentChoice.hpp
        network/messages/RequestGameOperation.hpp
        network/messages/GameStatus.hpp
        network/messages/RequestGamePause.hpp
        network/messages/RequestMetaInformation.hpp
        network/messages/Strike.hpp
        network/messages/RequestReplay.hpp
        network/messages/Replay.hpp
        network/messages/StatisticsMessage.hpp)

add_library(${PROJECT_NAME} SHARED ${SOURCE})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMMON_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -mtune=native -march=native)
target_link_libraries(${PROJECT_NAME}
        PUBLIC nlohmann_json::nlohmann_json
        PRIVATE uuid $<$<CONFIG:Debug>:--coverage>)
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/datatypes>)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${HEADER} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

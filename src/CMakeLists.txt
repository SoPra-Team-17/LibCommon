cmake_minimum_required(VERSION 3.10)
project(SopraCommon)

find_package(nlohmann_json REQUIRED)

set(SOURCE
        datatypes/gadgets/Gadget.cpp
        datatypes/gadgets/WiretapWithEarplugs.cpp
        datatypes/gadgets/Cocktail.cpp
        datatypes/gameplay/CharacterOperation.cpp
        datatypes/gameplay/BaseOperation.cpp
        datatypes/gameplay/Exfiltration.cpp
        datatypes/gameplay/GadgetAction.cpp
        datatypes/gameplay/GambleAction.cpp
        datatypes/gameplay/Movement.cpp
        datatypes/gameplay/PropertyAction.cpp
        datatypes/gameplay/CatAction.cpp
        datatypes/gameplay/JanitorAction.cpp
        datatypes/gameplay/SpyAction.cpp
        datatypes/gameplay/RetireAction.cpp
        datatypes/character/Character.cpp
        datatypes/character/CharacterInformation.cpp
        datatypes/character/CharacterDescription.cpp
        datatypes/character/CharacterSet.cpp
        datatypes/character/FactionEnum.hpp
        gameLogic/execution/ActionExecutor_Cat.cpp
        gameLogic/execution/ActionExecutor_Exfiltration.cpp
        gameLogic/execution/ActionExecutor_Gadget.cpp
        gameLogic/execution/ActionExecutor_Gamble.cpp
        gameLogic/execution/ActionExecutor_Janitor.cpp
        gameLogic/execution/ActionExecutor_Movement.cpp
        gameLogic/execution/ActionExecutor_Property.cpp
        gameLogic/execution/ActionExecutor_Retire.cpp
        gameLogic/execution/ActionExecutor_Spy.cpp
        gameLogic/execution/gadget/GadgetExecutor.cpp
        gameLogic/execution/ActionExecutor.cpp
        gameLogic/execution/gadget/HairDryer.cpp
        gameLogic/execution/gadget/MoleDie.cpp
        gameLogic/execution/gadget/BowlerBlade.cpp
        gameLogic/execution/gadget/TechnicolorPrism.cpp
        gameLogic/execution/gadget/Nugget.cpp
        gameLogic/execution/gadget/RocketPen.cpp
        gameLogic/execution/gadget/Grapple.cpp
        gameLogic/execution/gadget/Jetpack.cpp
        gameLogic/execution/gadget/GasGloss.cpp
        gameLogic/generation/ActionGenerator_Server.cpp
        datatypes/matchconfig/MatchConfig.cpp
        datatypes/scenario/Scenario.cpp
        datatypes/scenario/Scenario.cpp
        datatypes/scenario/FieldMap.cpp
        datatypes/scenario/Field.cpp
        datatypes/statistics/StatisticsEntry.cpp
        datatypes/statistics/Statistics.cpp
        datatypes/gameplay/State.cpp
        gameLogic/generation/ActionGenerator_Server.cpp
        gameLogic/validation/ActionValidator_Gadget.cpp
        gameLogic/validation/ActionValidator_Gamble.cpp
        gameLogic/validation/ActionValidator_Movement.cpp
        gameLogic/validation/ActionValidator_Property.cpp
        gameLogic/validation/ActionValidator.cpp
        gameLogic/validation/ActionValidator_Retire.cpp
        gameLogic/validation/ActionValidator_Spy.cpp
        gameLogic/validation/gadget/GadgetValidator.cpp
        gameLogic/validation/gadget/Hairdryer.cpp
        gameLogic/validation/gadget/RocketPen.cpp
        gameLogic/validation/gadget/TechnicolourPrism.cpp
        gameLogic/validation/gadget/PoisonPills.cpp
        gameLogic/validation/gadget/LaserCompact.cpp
        gameLogic/validation/gadget/MoleDie.cpp
        gameLogic/validation/gadget/GasGloss.cpp
        gameLogic/validation/gadget/MothballPouch.cpp
        gameLogic/validation/gadget/FogTin.cpp
        gameLogic/validation/gadget/Grapple.cpp
        gameLogic/validation/gadget/Jetpack.cpp
        gameLogic/validation/gadget/MagneticWatch.cpp
        gameLogic/validation/gadget/WiretapWithEarplugs.cpp
        gameLogic/validation/gadget/ChickenFeed.cpp
        gameLogic/validation/gadget/Nugget.cpp
        gameLogic/validation/gadget/MirrorOfWilderness.cpp
        gameLogic/validation/gadget/PocketLitter.cpp
        gameLogic/validation/gadget/DiamondCollar.cpp
        gameLogic/validation/gadget/Cocktail.cpp
        gameLogic/validation/gadget/BowlerBlade.cpp
        gameLogic/execution/property/PropertyExecutor.cpp
        gameLogic/execution/property/BangAndBurn.cpp
        gameLogic/execution/property/Observation.cpp
        gameLogic/execution/gadget/MoleDie.cpp
        gameLogic/execution/gadget/BowlerBlade.cpp
        gameLogic/execution/gadget/TechnicolorPrism.cpp
        gameLogic/execution/gadget/GasGloss.cpp
        gameLogic/generation/ActionGenerator_Server.cpp
        gameLogic/execution/gadget/LaserCompact.cpp
        gameLogic/execution/gadget/DiamondCollar.cpp
        gameLogic/execution/gadget/ChickenFeed.cpp
        gameLogic/execution/gadget/MirrorOfWilderness.cpp
        gameLogic/execution/gadget/Nugget.cpp
        gameLogic/execution/gadget/RocketPen.cpp
        network/messages/EquipmentChoice.cpp
        network/messages/Error.cpp
        network/messages/GameLeave.cpp
        network/messages/GameLeft.cpp
        network/messages/GameOperation.cpp
        network/messages/GamePause.cpp
        network/messages/Hello.cpp
        network/messages/HelloReply.cpp
        network/MessageContainer.cpp
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
        network/messages/StatisticsMessage.cpp
        util/UUID.cpp
        util/Point.cpp
        util/GameLogicUtils.cpp
        )


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
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.hpp"
        )

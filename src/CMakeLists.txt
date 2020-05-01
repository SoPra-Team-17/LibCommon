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
        datatypes/execution/ActionExecutor_Cat.cpp
        datatypes/execution/ActionExecutor_Exfiltration.cpp
        datatypes/execution/ActionExecutor_Gadget.cpp
        datatypes/execution/ActionExecutor_Gamble.cpp
        datatypes/execution/ActionExecutor_Janitor.cpp
        datatypes/execution/ActionExecutor_Movement.cpp
        datatypes/execution/ActionExecutor_Property.cpp
        datatypes/execution/ActionExecutor_Retire.cpp
        datatypes/execution/ActionExecutor_Spy.cpp
        datatypes/execution/gadget/GadgetExecutor.cpp
        datatypes/execution/ActionExecutor.cpp
        datatypes/execution/gadget/HairDryer.cpp
        datatypes/matchconfig/MatchConfig.cpp
        datatypes/scenario/Scenario.cpp
        datatypes/scenario/Scenario.cpp
        datatypes/scenario/FieldMap.cpp
        datatypes/scenario/Field.cpp
        datatypes/statistics/StatisticsEntry.cpp
        datatypes/statistics/Statistics.cpp
        datatypes/gameplay/State.cpp
        datatypes/validation/ExfiltrationValidator.cpp
        datatypes/validation/GadgetSwitch.cpp
        datatypes/validation/GambleValidator.cpp
        datatypes/validation/MovementValidator.cpp
        datatypes/validation/PropertyValidator.cpp
        datatypes/validation/ActionValidator.cpp
        datatypes/validation/ActionValidator_Cat.cpp
        datatypes/validation/ActionValidator_Janitor.cpp
        datatypes/validation/ActionValidator_Retire.cpp
        datatypes/validation/ActionValidator_Spy.cpp
        datatypes/validation/gadget/GadgetValidator.cpp
        datatypes/validation/gadget/Hairdryer.cpp
        datatypes/validation/gadget/RocketPen.cpp
        datatypes/validation/gadget/TechnicolourPrism.cpp
        datatypes/validation/gadget/PoisonPills.cpp
        datatypes/validation/gadget/LaserCompact.cpp
        datatypes/validation/gadget/MoleDie.cpp
        datatypes/validation/gadget/GasGloss.cpp
        datatypes/validation/gadget/MothballPouch.cpp
        datatypes/validation/gadget/FogTin.cpp
        datatypes/validation/gadget/Grapple.cpp
        datatypes/validation/gadget/Jetpack.cpp
        datatypes/validation/gadget/MagneticWatch.cpp
        datatypes/validation/gadget/WiretapWithEarplugs.cpp
        datatypes/validation/gadget/ChickenFeed.cpp
        datatypes/validation/gadget/Nugget.cpp
        datatypes/validation/gadget/MirrorOfWilderness.cpp
        datatypes/validation/gadget/PocketLitter.cpp
        datatypes/validation/gadget/DiamondCollar.cpp
        datatypes/validation/gadget/Cocktail.cpp
        datatypes/validation/gadget/BowlerBlade.cpp
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
        util/GadgetUtils.cpp
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

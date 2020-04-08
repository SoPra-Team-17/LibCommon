cmake_minimum_required(VERSION 3.10)
project(SopraCommon)

# build options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -mtune=native -march=native")

find_package(nlohmann_json REQUIRED)

set(SOURCE
        datatypes/gadgets/Gadget.cpp
        datatypes/gadgets/WiretapWithEarplugs.cpp
        datatypes/gadgets/Cocktail.cpp
        datatypes/character/Character.cpp
        datatypes/character/CharacterInformation.cpp
        datatypes/character/CharacterDescription.cpp
        datatypes/matchconfig/MatchConfig.cpp
        datatypes/scenario/Scenario.cpp
        network/messages/ConfigDelivery.cpp
        network/messages/ConnectionError.cpp
        network/messages/EquipmentChoice.cpp
        network/messages/GameLeave.cpp
        network/messages/GameLeft.cpp
        network/messages/MessageContainer.cpp
        util/UUID.cpp
        util/Point.cpp
        )

set(INCLUDE
        datatypes/gadgets/Gadget.hpp
        datatypes/gadgets/WiretapWithEarplugs.hpp
        datatypes/gadgets/Cocktail.hpp
        datatypes/character/Character.hpp
        datatypes/character/CharacterInformation.hpp
        datatypes/character/CharacterDescription.hpp
        datatypes/character/PropertyEnum.hpp
        datatypes/matchconfig/MatchConfig.hpp
        datatypes/scenario/Scenario.hpp
        network/messages/ConfigDelivery.hpp
        network/messages/ConnectionError.hpp
        network/messages/EquipmentChoice.hpp
        network/messages/GameLeave.hpp
        network/messages/GameLeft.hpp
        network/messages/MessageContainer.hpp
        network/messages/MessageTypeEnum.hpp
        network/ErrorTypeEnum.hpp
        util/UUID.hpp
        util/Point.hpp
        )

include_directories(.)
include_directories(src)
include_directories(datatypes)

add_library(${PROJECT_NAME} SHARED ${SOURCE})
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/lib)
install(FILES ${INCLUDE} DESTINATION /usr/include/${PROJECT_NAME})

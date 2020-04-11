cmake_minimum_required(VERSION 3.10)
project(SopraCommon)

# build options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -mtune=native -march=native")

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
        datatypes/scenario/FieldMap.cpp
        datatypes/scenario/Field.cpp
        util/UUID.cpp
        util/Point.cpp
        )

set(INCLUDE
        datatypes/gadgets/Gadget.hpp
        datatypes/gadgets/WiretapWithEarplugs.hpp
        datatypes/gadgets/Cocktail.hpp
        datatypes/gameplay/Exfiltration.hpp
        datatypes/gameplay/GadgetAction.hpp
        datatypes/gameplay/GambleAction.hpp
        datatypes/gameplay/Movement.hpp
        datatypes/gameplay/Operation.hpp
        datatypes/gameplay/OperationEnum.hpp
        datatypes/gameplay/PropertyAction.hpp
        datatypes/character/Character.hpp
        datatypes/character/CharacterInformation.hpp
        datatypes/character/CharacterDescription.hpp
        datatypes/character/PropertyEnum.hpp
        datatypes/matchconfig/MatchConfig.hpp
        datatypes/scenario/Scenario.hpp
        datatypes/scenario/FieldMap.hpp
        datatypes/scenario/Field.hpp
        datatypes/scenario/FieldStateEnum.hpp
        util/UUID.hpp
        util/Point.hpp
        )

include_directories(.)
include_directories(src)
include_directories(datatypes)

add_library(${PROJECT_NAME} SHARED ${SOURCE})
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json uuid)

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/lib)
install(FILES ${INCLUDE} DESTINATION /usr/include/${PROJECT_NAME})

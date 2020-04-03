cmake_minimum_required(VERSION 3.10)
project(SopraCommon)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE
		datatypes/gadgets/Gadget.cpp
		datatypes/gadgets/WiretapWithEarplugs.cpp
		datatypes/gadgets/Cocktail.cpp
		datatypes/character/Character.cpp
		datatypes/character/CharacterInformation.cpp
		datatypes/character/CharacterDescription.cpp
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
		util/UUID.hpp
		util/Point.hpp
		)

include_directories(.)
include_directories(src)
include_directories(datatypes)

add_library(${PROJECT_NAME} SHARED ${SOURCE})

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/lib)
install(FILES ${INCLUDE} DESTINATION /usr/include/${PROJECT_NAME})
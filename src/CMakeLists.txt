cmake_minimum_required(VERSION 3.10)
project(SopraCommon)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE
		library.cpp
		Gadget.cpp
		gadgets/WiretapWithEarplugs.cpp
		gadgets/Cocktail.cpp
		util/UUID.cpp
		)

include_directories(.)

add_library(${PROJECT_NAME} SHARED ${SOURCE})

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/lib)
install(FILES ${INCLUDE} DESTINATION /usr/include/${PROJECT_NAME})
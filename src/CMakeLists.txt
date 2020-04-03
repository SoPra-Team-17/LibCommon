cmake_minimum_required(VERSION 3.10)
project(SopraCommon)

# build options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif (NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror -mtune=native -march=native")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("\n##########################")
    message("###### DEBUG BUILD #######")
    message("##########################\n")
else ()
    message("\n############################")
    message("###### RELEASE BUILD #######")
    message("############################\n")
endif ()


find_package(nlohmann_json REQUIRED)

set(SOURCE
        library.cpp
        Gadget.cpp
        gadgets/WiretapWithEarplugs.cpp
        gadgets/Cocktail.cpp
        util/UUID.cpp)

set(INCLUDE
        Gadget.hpp
        gadgets/Cocktail.hpp
        gadgets/WiretapWithEarplugs.hpp
        util/UUID.hpp)

include_directories(.)

add_library(${PROJECT_NAME} SHARED ${SOURCE})
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/lib)
install(FILES ${INCLUDE} DESTINATION /usr/include/${PROJECT_NAME})

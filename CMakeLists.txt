cmake_minimum_required(VERSION 3.10)
project(LibCommon)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

option(LIBCOMMON_TESTS "Build the tests" ON)
if (LIBCOMMON_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif ()
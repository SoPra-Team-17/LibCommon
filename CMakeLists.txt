cmake_minimum_required(VERSION 3.10)
project(LibCommon)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

option(LIBCOMMON_TESTS "Build the tests" ON)
if (LIBCOMMON_TESTS)
    # Download and unpack googletest at configure time
    configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
            )
    if (result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif ()

    execute_process(COMMAND "${CMAKE_COMMAND}" --build .
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
            )
    if (result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif ()


    # Add googletest directly to the build
    add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
            "${CMAKE_BINARY_DIR}/googletest-build"
            )

    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif ()
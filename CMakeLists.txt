cmake_minimum_required(VERSION 3.10)
project(SampleLibrary)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE
	library.cpp
	)

set(INCLUDE
	library.cpp
	)

add_library(SampleLibrary SHARED ${SOURCE})

install(TARGETS SampleLibrary DESTINATION /usr/lib)
install(FILES ${INCLUDE} DESTINATION /usr/include/SampleLibrary)
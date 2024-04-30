cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "C:/Programs/gcc11-64-winlibs/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/Programs/gcc11-64-winlibs/bin/g++.exe")

project(physics)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    engine/core/test.cpp
    engine/core/collision_detection.cpp
    engine/core/collision_resolution.cpp
    engine/core/engine.cpp
    # Add more source files here if needed
)

# Add header files
set(HEADERS
    engine/core/cuboid_rigidbody.h
    engine/core/environment.h
    engine/core/rigidbody.h
    engine/geometry/matrix.h
    engine/geometry/vector.h
    # Add more header files here if needed
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
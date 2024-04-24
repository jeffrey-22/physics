cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "C:/Programs/gcc11-64-winlibs/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/Programs/gcc11-64-winlibs/bin/g++.exe")

project(physics)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add Eigen include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/eigen)

# Add executable
add_executable(test engine/core/test.cpp)
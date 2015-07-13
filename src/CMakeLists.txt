cmake_minimum_required(VERSION 3.2)
project(Diplomka)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Diplomka ${SOURCE_FILES} core/core.h core/geometry.h)
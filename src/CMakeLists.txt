cmake_minimum_required(VERSION 3.2)
project(Diplomka)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
                 core/geometry.cpp
                 core/camera.cpp
                 core/light.cpp
                 core/scene.cpp)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(Diplomka ${SOURCE_FILES} core/film.h core/film.cpp core/brdf.h core/brdf.cpp core/integrator.h core/integrator.cpp core/material.h core/material.cpp core/primitive.h core/primitive.cpp core/renderer.h core/renderer.cpp acceleration/bruteforce.h acceleration/bruteforce.cpp acceleration/grid.h acceleration/grid.cpp)
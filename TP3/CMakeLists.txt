cmake_minimum_required(VERSION 3.1)
project(TP3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(TP3 ${SOURCE_FILES} bloc.cpp bloc.h vorace.h vorace.cpp blocrotation.cpp blocrotation.h )
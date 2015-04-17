cmake_minimum_required(VERSION 2.8)
project(TP3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(TP3 ${SOURCE_FILES} bloc.cpp bloc.h vorace.h vorace.cpp blocrotation.cpp blocrotation.h MetaHeuristique.cpp MetaHeuristique.h)

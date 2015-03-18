cmake_minimum_required(VERSION 2.8.4)
project(TP1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(MERGE_FILES merge.cpp)
add_executable(Merge ${MERGE_FILES})

add_executable(Selection selection.cpp)

add_executable(mergeSeuil mergeSeuil.cpp)

add_executable(couting counting.cpp)
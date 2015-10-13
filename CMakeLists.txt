cmake_minimum_required(VERSION 3.3)
project(BinTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES lab2.cpp nodedata.cpp nodedata.h BinTree.cpp BinTree.h)
add_executable(BinTree ${SOURCE_FILES})
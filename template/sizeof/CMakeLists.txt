cmake_minimum_required(VERSION 3.5)
project(sizeof)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp)
add_executable(sizeof ${SOURCE_FILES})

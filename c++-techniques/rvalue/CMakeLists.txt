cmake_minimum_required(VERSION 3.5)
project(cpp11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp)
add_executable(cpp11 ${SOURCE_FILES})

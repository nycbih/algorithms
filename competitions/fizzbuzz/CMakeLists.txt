cmake_minimum_required(VERSION 3.5)
project(fizzbuzz)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp)
add_executable(fizzbuzz ${SOURCE_FILES})

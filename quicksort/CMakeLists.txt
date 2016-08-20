cmake_minimum_required(VERSION 3.5)
project(quicksort)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
SET (${CMAKE_CXX_FLAGS} CMAKE_CXX_FLAGS  "-Wall")
SET (${CMAKE_CXX_FLAGS} CMAKE_CXX_FLAGS_DEBUG "-g")

set(SOURCE_FILES main.cpp)
add_executable(quicksort ${SOURCE_FILES})

cmake_minimum_required (VERSION 2.6)
project (Neuro)
set(CMAKE_CXX_FLAGS "-O3 -W -Wall -pedantic -std=c++11")

add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(neuro neurone.cpp main_neurone.cpp)



cmake_minimum_required(VERSION 2.8)

project(cctest)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(test_thread test_thread.cc)
add_executable(test_c++11 test_c++11.cc)

cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)

project(point)
add_executable(point point.cpp)
target_link_libraries(point properties)

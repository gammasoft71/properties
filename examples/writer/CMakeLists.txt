cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)

project(writer)
add_executable(writer writer.cpp)
target_link_libraries(writer properties)

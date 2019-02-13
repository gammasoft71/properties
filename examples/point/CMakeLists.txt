cmake_minimum_required(VERSION 3.2)

project(point)
find_package(xtd.properties REQUIRED)
add_executable(point point.cpp)
target_link_libraries(point xtd.properties)

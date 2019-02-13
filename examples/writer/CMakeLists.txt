cmake_minimum_required(VERSION 3.2)

project(writer)
find_package(xtd.properties REQUIRED)
add_executable(writer writer.cpp)
target_link_libraries(writer xtd.properties)

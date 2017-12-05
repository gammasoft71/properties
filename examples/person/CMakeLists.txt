cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)

project(person)
add_executable(person person.cpp)
target_link_libraries(person properties)

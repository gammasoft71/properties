cmake_minimum_required(VERSION 3.2)

project(person)
find_package(xtd.properties REQUIRED)
add_executable(person person.cpp)
target_link_libraries(person xtd.properties)

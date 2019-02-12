cmake_minimum_required(VERSION 3.8)

project(manualtests)

add_executable(manualtests main.cpp)
target_link_libraries(manualtests properties)

cmake_minimum_required(VERSION 3.20)

project(writer)
find_package(xtd.properties REQUIRED)
add_executable(writer writer.cpp)
target_link_libraries(writer xtd.properties)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "xtd.properties")

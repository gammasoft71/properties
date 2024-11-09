cmake_minimum_required(VERSION 3.20)

project(prop_point)
find_package(xtd.properties REQUIRED)
add_executable(prop_point point.cpp)
target_link_libraries(prop_point xtd.properties)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "xtd.properties")

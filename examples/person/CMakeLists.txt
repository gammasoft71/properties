cmake_minimum_required(VERSION 3.20)

project(person)
find_package(xtd.properties REQUIRED)
add_executable(person person.cpp)
target_link_libraries(person xtd.properties)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "xtd.properties")

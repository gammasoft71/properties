cmake_minimum_required(VERSION 3.20)

#Project
project(xtd.properties.manual_tests)
set(SOURCES
  src/manual_tests.cpp
)
source_group(src FILES ${SOURCES})

# Options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Target
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} xtd.properties)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "xtd/tests")

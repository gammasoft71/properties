cmake_minimum_required(VERSION 3.3)

# Project
project(xtd.properties.unit_tests)
set(SOURCES
  src/main.cpp 
  src/properties_readonly.cpp
  src/properties_readwrite.cpp
  src/properties_writeonly.cpp
)
source_group(src FILES ${SOURCES})

# Options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Target
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} xtd.properties xtd.tunit)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "xtd/tests")

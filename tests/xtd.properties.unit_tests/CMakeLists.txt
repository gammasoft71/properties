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

# External projects
include(ExternalProject)
ExternalProject_Add(catch GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v2.6.0 GIT_SHALLOW 1 CMAKE_ARGS -DCATCH_BUILD_TESTING=OFF -DCATCH_INSTALL_DOCS=OFF -DCATCH_INSTALL_HELPERS=OFF -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR})
include_directories(SYSTEM ${CMAKE_BINARY_DIR}/include)

# Options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Target
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} xtd.properties)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "xtd/tests")
add_dependencies(${PROJECT_NAME} catch)

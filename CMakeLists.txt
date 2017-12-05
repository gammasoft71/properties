cmake_minimum_required(VERSION 3.8)

project(properties VERSION 1.0.0)
set(PROJECT_BRIEF "another c#-like property accessor for c++.")
set(PROJECT_AUTHOR "gammasoft71")
set(PROJECT_LOGO "")

# Set project options
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTS "Build tests" OFF)
option(ENABLE_COVERAGE "Enable code coverage" OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (ENABLE_COVERAGE AND UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
  set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} --coverage")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
else()
  set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
endif()

if (WIN32 STREQUAL "1")
  set(EXECUTABLE_EXTENSION .exe)
endif()

if (CMAKE_BUILD_TYPE)
  set(PROPERTIES_BUILD_TYPE ${CMAKE_BUILD_TYPE})
else()
  set(PROPERTIES_BUILD_TYPE Debug)
endif()

list(APPEND CPPCHECK_ARGS
  --enable=warning,style,performance,portability,unusedFunction
  --std=c++14
  --verbose
  --error-exitcode=1
  --language=c++
  --suppressions-list=${CMAKE_CURRENT_BINARY_DIR}/cppcheck_false_positive.txt
  --template='[{file}:{line}]: ({severity}) {{id}} {message}'
  -DMAIN=main
  -I ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/examples
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/tests
  )

list(APPEND ASTYLE_ARGS
  --style=java
  --indent=spaces=2
  --attach-namespaces
  --attach-classes
  --attach-inlines
  --attach-extern-c
  --attach-closing-while
  --indent-namespaces
  --indent-after-parens
  --indent-preproc-define
  --indent-preproc-cond
  --indent-col1-comments
  --pad-oper
  --pad-comma
  --unpad-paren
  --fill-empty-lines
  --align-pointer=type
  --align-reference=type
  --remove-braces
  --keep-one-line-blocks
  --keep-one-line-statements
  --convert-tabs
  --close-templates
  --suffix=none
  --recursive
  ${CMAKE_SOURCE_DIR}/examples/*.cpp
  ${CMAKE_SOURCE_DIR}/include/*.hpp
  ${CMAKE_SOURCE_DIR}/tests/*.cpp
  )

# Include Modules
include(ExternalProject)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cppcheck_false_positive.txt ${CMAKE_CURRENT_BINARY_DIR}/cppcheck_false_positive.txt @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/.doxygen.txt ${CMAKE_CURRENT_BINARY_DIR}/doxygen.txt @ONLY)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/reference_guide)

file(WRITE .appveyor.yml "version: ${PROJECT_VERSION}.{build}\nimage: Visual Studio 2017\nenvironment:\n  matrix:\n  - BUILD_WIN32: true\n  - BUILD_WIN64: true\nbuild_script:\n  - cmd: scripts\\appveyor\\build_vs2017.bat\ntest_script:\n  - cmd: scripts\\appveyor\\test.bat\n")

include_directories(include)
include_directories(SYSTEM ${CMAKE_BINARY_DIR}/include)

message(STATUS "Informations")
message(STATUS "  CMake version [${CMAKE_VERSION}]")
message(STATUS "  System [${CMAKE_SYSTEM}]")
message(STATUS "  Compiler [${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}]")
message(STATUS "  Build type [${CMAKE_BUILD_TYPE}]")
if (UNIX)
  message(STATUS "  Code coverage [${ENABLE_COVERAGE}]")
else()
  message(STATUS "  Code coverage [NOT AVAIBLE]")
endif()
message(STATUS "  Install prefix [${CMAKE_INSTALL_PREFIX}]")
message(STATUS "  Output path [${EXECUTABLE_OUTPUT_PATH}]")
message(STATUS "  Executable extension [${EXECUTABLE_EXTENSION}]")

message(STATUS "Find packages")
find_package(Git REQUIRED QUIET)
if (Git_FOUND)
  message(STATUS "  [X] Git ${GIT_VERSION_STRING}")
else()
  message(STATUS "  [ ] Git")
endif()
find_package(DOXYGEN QUIET)
if (Doxygen_FOUND)
  message(STATUS "  [X] Doxygen ${DOXYGEN_VERSION}")
else()
  message(STATUS "  [ ] Doxygen")
endif()

message(STATUS "External projeccts")
ExternalProject_Add(astyle GIT_REPOSITORY https://github.com/Bareflank/astyle.git GIT_TAG v1.2 GIT_SHALLOW 1 CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR})
message(STATUS "  [X] astyle v1.2")
ExternalProject_Add(cppcheck GIT_REPOSITORY https://github.com/danmar/cppcheck.git GIT_TAG 1.81 GIT_SHALLOW 1 CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR})
message(STATUS "  [X] cppcheck 1.81")
ExternalProject_Add(catch GIT_REPOSITORY  https://github.com/catchorg/Catch2.git GIT_TAG v2.0.1 GIT_SHALLOW 1 CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR})
message(STATUS "  [X] catch 2.0.1")

message(STATUS "Generating properties ${properties_VERSION}")
message(STATUS "  [X] interface")
add_library(properties INTERFACE)
target_include_directories(properties INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
install(FILES include/properties/properties.hpp DESTINATION include/properties)

if (BUILD_EXAMPLES)
  message(STATUS "  [X] examples")
  add_subdirectory("examples")
else()
  message(STATUS "  [ ] examples")
endif()

if (BUILD_TESTS)
  message(STATUS "Building properties Tests")
  enable_testing()

  message(STATUS "  [X] unittests")
  add_subdirectory("tests/unittests")
else()
  message(STATUS "  [ ] unittests")
endif()

#install(EXPORT properties DESTINATION cmake)
#install(FILES scripts/cmake/propertiesConfig.cmake scripts/cmake/propertiesDependencies.cmake DESTINATION cmake)

message(STATUS "Custom targets")

message(STATUS "  [X] ${PROJECT_NAME}.check")
add_custom_target(${PROJECT_NAME}.check COMMAND ${CMAKE_BINARY_DIR}/bin/cppcheck${EXECUTABLE_EXTENSION} ${CPPCHECK_ARGS} COMMENT "running cppcheck" DEPENDS cppcheck)

message(STATUS "  [X] ${PROJECT_NAME}.format")
add_custom_target(${PROJECT_NAME}.format COMMAND ${CMAKE_BINARY_DIR}/bin/astyle${EXECUTABLE_EXTENSION} ${ASTYLE_ARGS} COMMENT "running astyle" DEPENDS astyle)

message(STATUS "  [X] ${PROJECT_NAME}.git_check")
add_custom_target(${PROJECT_NAME}.git_check COMMAND git diff --check HEAD^ COMMENT "running git check")

# add custom target ${PROJECT_NAME}.install to install project.
message(STATUS "  [X] ${PROJECT_NAME}.install")
if (WIN32)
  add_custom_target(${PROJECT_NAME}.install "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target install --config ${PROPERTIES_BUILD_TYPE} DEPENDS ${PROJECT_NAME} COMMENT "Installing ${PROJECT_NAME}")
else(UNIX)
  add_custom_target(${PROJECT_NAME}.install "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target install -- -j8 DEPENDS ${PROJECT_NAME} COMMENT "Installing ${PROJECT_NAME}")
endif()

# add custom target ${PROJECT_NAME}.refefrence_guide to generate doxygen project reference guide.
if (DOXYGEN_FOUND)
  message(STATUS "  [X] ${PROJECT_NAME}.reference_guide")
  add_custom_target(${PROJECT_NAME}.reference_guide ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen.txt WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/reference_guide COMMENT "Doxygen Reference Guide generation" VERBATIM)
else()
  message(STATUS "  [ ] ${PROJECT_NAME}.reference_guide")
endif()

# add custom target ${PROJECT_NAME}.tests to run project tests.
message(STATUS "  [X] ${PROJECT_NAME}.tests")
add_custom_target(${PROJECT_NAME}.tests COMMAND ctest --output-on-failure -C ${PROPERTIES_BUILD_TYPE} DEPENDS ${PROJECT_NAME}.install)

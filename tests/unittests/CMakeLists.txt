cmake_minimum_required(VERSION 3.8)

project(unittests)

add_executable(unittests main.cpp properties_readonly.cpp properties_readwrite.cpp properties_writeonly.cpp)
target_link_libraries(unittests properties )
add_dependencies(unittests catch)

add_test(NAME ${PROJECT_NAME} COMMAND $<TARGET_FILE_NAME:${PROJECT_NAME}> WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

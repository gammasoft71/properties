cmake_minimum_required(VERSION 3.20)

# Solution
project(src)

# Projects
add_subdirectory(xtd_properties)
if (IS_MAIN_PROJECT)
  add_subdirectory(xtd_tunit)
endif ()

######################## project details ##########################
cmake_minimum_required(VERSION 3.13)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# project detail
project(mcpp VERSION 1.0 DESCRIPTION "Statistical model")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../out)

# cpp standard (c++14)
set(CMAKE_CXX_STANDARD 14)

include_directories(includes)
include_directories(test/)

add_subdirectory(lib/googletest EXCLUDE_FROM_ALL)

# reg
add_executable(test_reg test/reg_test.cpp)

# misc
add_executable(test_misc test/misc_test.cpp)

# int 
add_executable(test_int test/int_test.cpp)

target_link_libraries(test_reg gtest pthread) 
target_link_libraries(test_misc gtest pthread) 
target_link_libraries(test_int gtest pthread) 
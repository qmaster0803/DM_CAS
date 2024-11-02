# General
cmake_minimum_required(VERSION 3.20)
project(DM_CAS)

# Libraries
add_library(Algo    STATIC lib/algo.cpp   )

add_library(Natural STATIC lib/Natural.cpp)
target_link_libraries(Natural Algo)

add_library(Interactive_shell STATIC lib/Interactive_shell.cpp)
target_link_libraries(Interactive_shell ncurses)

# Main executable
add_executable(DM_CAS main.cpp)
target_link_libraries(DM_CAS Interactive_shell)

# Testing
enable_testing()

add_executable(Natural_test tests/Natural_test.cpp)
target_link_libraries(Natural_test Natural gtest_main gtest)

include(GoogleTest)
gtest_discover_tests(Natural_test Integer_tests)

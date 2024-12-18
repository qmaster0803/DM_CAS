# General
cmake_minimum_required(VERSION 3.20)
project(DM_CAS)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# for debug
set(CMAKE_BUILD_TYPE Debug)

# Libraries
add_library(Algo    STATIC lib/algo.cpp   )

add_library(Natural STATIC lib/Natural.cpp)
target_link_libraries(Natural Algo)

add_library(Integer STATIC lib/Integer.cpp)
target_link_libraries(Integer Natural)

add_library(Rational STATIC lib/Rational.cpp)
target_link_libraries(Rational Integer)

add_library(Polynomial STATIC lib/Polynomial.cpp)
target_link_libraries(Polynomial Rational)

add_library(Parser STATIC lib/Parser.cpp)
target_link_libraries(Parser Polynomial)

add_library(Interactive_shell STATIC lib/Interactive_shell.cpp)
target_link_libraries(Interactive_shell Parser ncurses)

# Main executable
add_executable(DM_CAS main.cpp)
target_link_libraries(DM_CAS Interactive_shell)

# Testing
enable_testing()

add_executable(Natural_test tests/Natural_test.cpp)
target_link_libraries(Natural_test Natural gtest_main gtest)

add_executable(Integer_test tests/Integer_test.cpp)
target_link_libraries(Integer_test Integer gtest_main gtest)

add_executable(Rational_test tests/Rational_test.cpp)
target_link_libraries(Rational_test Rational gtest_main gtest)

add_executable(backend_test tests/backend_test.cpp)
target_link_libraries(backend_test Natural Integer Rational Polynomial gtest_main gtest)

add_executable(Polynomial_test tests/Polynomial_test.cpp)
target_link_libraries(Polynomial_test Polynomial gtest_main gtest)

add_executable(Parser_test tests/Parser_test.cpp)
target_link_libraries(Parser_test Parser Natural Integer Rational Polynomial gtest_main gtest)

include(GoogleTest)
gtest_discover_tests(Natural_test)
gtest_discover_tests(Integer_test)
gtest_discover_tests(Rational_test)
gtest_discover_tests(Polynomial_test)
gtest_discover_tests(backend_test)
gtest_discover_tests(Parser_test)

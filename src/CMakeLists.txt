cmake_minimum_required(VERSION 3.25)
project(DM_CAS)

add_library(Interactive_shell lib/Interactive_shell.cpp)
target_link_libraries(Interactive_shell ncurses)

add_executable(DM_CAS main.cpp)
target_link_libraries(DM_CAS Interactive_shell)

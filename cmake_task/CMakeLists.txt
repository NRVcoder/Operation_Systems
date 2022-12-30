cmake_minimum_required(VERSION 3.25)

project(root_project)

add_executable(myExe main.cpp)

target_link_libraries(root_project mylib)
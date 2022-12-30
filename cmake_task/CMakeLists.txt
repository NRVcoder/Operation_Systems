cmake_minimum_required(VERSION 3.25)

project(root_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(myExe main.cpp)

add_subdirectory(stack)

target_include_directories(root_project STATIC stack/include/ThreadSafeStack.h solver/Solver.h)

target_link_libraries(myExe mylib)
cmake_minimum_required(VERSION 3.25)

project(test_project)

add_Library(mylib  src/ThreadSafeStack.cpp include/ThreadSafeStack.h)

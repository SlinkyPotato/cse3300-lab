cmake_minimum_required(VERSION 3.7)
project(cse3300_lab)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        lab3.pdf
        student.c)

add_executable(cse3300_lab ${SOURCE_FILES})
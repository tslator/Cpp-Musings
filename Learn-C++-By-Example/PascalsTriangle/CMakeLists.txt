cmake_minimum_required(VERSION 4.0)
project(PascalsTriangle)

set(CMAKE_CXX_STANDARD 20)

add_executable(PascalsTriangle main.cpp
        types.h
        triangle.cpp
        triangle.h)

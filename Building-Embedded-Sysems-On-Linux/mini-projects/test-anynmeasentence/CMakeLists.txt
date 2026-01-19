cmake_minimum_required(VERSION 4.0)
project(test_anynmeasentence)

set(CMAKE_CXX_STANDARD 20)

add_executable(test_anynmeasentence main.cpp
        anynmeasentence1.cpp
        anynmeasentence1.h
        anynmeasentence2.cpp
        anynmeasentence2.h)

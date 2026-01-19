cmake_minimum_required(VERSION 4.0)
project(CommandPattern)

set(CMAKE_CXX_STANDARD 20)

add_executable(CommandPattern main.cpp
        calculator.h
        CalculatorCommand.h
        Add.h
        Subtract.h
        Calculator.cpp)

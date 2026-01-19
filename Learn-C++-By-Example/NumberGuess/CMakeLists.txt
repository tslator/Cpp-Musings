cmake_minimum_required(VERSION 4.0)
project(NumberGuess)

set(CMAKE_CXX_STANDARD 20)

add_executable(NumberGuess main.cpp
        guess_random.cpp
        guess_random.h
        random_number.cpp
        random_number.h
        guess_prime.cpp
        guess_prime.h
        prime_number.cpp
        prime_number.h
        input_utils.cpp
        input_utils.h)

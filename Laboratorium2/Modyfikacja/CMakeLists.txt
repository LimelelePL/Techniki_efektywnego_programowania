cmake_minimum_required(VERSION 4.0)
project(modyfikacja)

set(CMAKE_CXX_STANDARD 11)

add_executable(modyfikacja main.cpp
        Number.cpp
        Number.h
        ComplexNumber.cpp
        ComplexNumber.h)

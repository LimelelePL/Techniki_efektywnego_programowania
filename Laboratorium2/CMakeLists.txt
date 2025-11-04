cmake_minimum_required(VERSION 4.0)
project(Laboratorium2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Laboratorium2 main.cpp
        Number.cpp
        Number.h
        Base256Number.cpp
        Base256Number.h)

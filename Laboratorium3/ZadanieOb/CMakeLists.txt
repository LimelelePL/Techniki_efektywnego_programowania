cmake_minimum_required(VERSION 4.0)
project(ZadanieOb)

set(CMAKE_CXX_STANDARD 11)

add_executable(ZadanieOb main.cpp
        Parser.cpp
        Parser.h
        Interface.cpp
        Interface.h
        Node.cpp
        Node.h
        Tree.cpp
        Tree.h)

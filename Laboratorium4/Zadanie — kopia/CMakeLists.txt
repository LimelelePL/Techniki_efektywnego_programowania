cmake_minimum_required(VERSION 4.0)
project(Zadanie)

set(CMAKE_CXX_STANDARD 11)

add_executable(Zadanie main.cpp
        Node.cpp
        Node.h
        Tree.cpp
        Tree.h
        Parser.cpp
        Parser.h
        Interface.cpp
        Interface.h
        Error.h
        Result.h
        Error.cpp
        Result.tpp
        ResultSaver.h
        ResultSaver.tpp
)

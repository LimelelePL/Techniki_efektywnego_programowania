cmake_minimum_required(VERSION 4.0)
project(Zadanie)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")

add_executable(Zadanie main.cpp
        Tree/Node.cpp
        Tree/Node.h
        Tree/Tree.cpp
        Tree/Tree.h
        Tree/Parser.cpp
        Tree/Parser.h
        Tree/Interface.cpp
        Tree/Interface.h
        Result/Error.h
        Result/Result.h
        Result/Error.cpp
        Result/Result.tpp
        Result/ResultSaver.h
        Result/ResultSaver.tpp
        SmartPointer/SmartPointer.h
        SmartPointer/RefCounter.cpp
        SmartPointer/RefCounter.h
)

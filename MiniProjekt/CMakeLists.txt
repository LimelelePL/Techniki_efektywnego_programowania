cmake_minimum_required(VERSION 4.0)
project(MiniProjekt)

set(CMAKE_CXX_STANDARD 23)

add_executable(MiniProjekt main.cpp
        VrpInstance.cpp
        InstanceReader.hpp
        InstanceReader.cpp
        GeneticAlgorithm.cpp
        GeneticAlgorithm.h
        Individual.cpp
        Individual.h
        Evaluator.cpp
        Evaluator.h
        RandomGenerator.cpp
        RandomGenerator.h
        ConstantValues.h
        Errors/Error.cpp
        Errors/Error.h
        Errors/Result.h)

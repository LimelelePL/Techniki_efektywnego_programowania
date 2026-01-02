//
// Created by Dominik on 02.01.2026.
//

#ifndef MINIPROJEKT_GENETICALGORITHM_H
#define MINIPROJEKT_GENETICALGORITHM_H
#include <vector>


class GeneticAlgorithm {
public:


private:
    int popSize;
    double crossProb;
    double mutProb;
    int maxIterations;
    std::vector<int> bestSolution;
};


#endif //MINIPROJEKT_GENETICALGORITHM_H
//
// Created by Dominik on 02.01.2026.
//

#ifndef MINIPROJEKT_GENETICALGORITHM_H
#define MINIPROJEKT_GENETICALGORITHM_H
#include <vector>

#include "Individual.h"


class GeneticAlgorithm {
public:
    GeneticAlgorithm(Evaluator &eval, int popSize, double crossProb, double mutProb, int maxIterations);
    void run();
    std::vector<int> getBestSolution;

private:
    int popSize;
    double crossProb;
    double mutProb;
    int maxIterations;
    std::vector<int> bestSolution;
    std::vector<Individual> population;
    Evaluator& eval;
    RandomGenerator gen;

    void crossPopulation();
    void genRandomPopulation();
    Individual& selectParents();
};


#endif //MINIPROJEKT_GENETICALGORITHM_H
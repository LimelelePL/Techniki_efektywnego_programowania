//
// Created by Dominik on 02.01.2026.
//

#ifndef MINIPROJEKT_GENETICALGORITHM_H
#define MINIPROJEKT_GENETICALGORITHM_H
#include <vector>

#include "Individual.h"


class GeneticAlgorithm {
public:
    GeneticAlgorithm(Evaluator &eval, RandomGenerator& generator, int popSize, double crossProb, double mutProb, int maxIterations);
    ~GeneticAlgorithm();
    void run();
    std::vector<int> getBestSolution;
    void printBest();
    void printDetailedBest();


private:
    int popSize;
    double crossProb;
    double mutProb;
    int maxIterations;
    Individual* bestSolution;
    std::vector<Individual> population;
    Evaluator& eval;
    RandomGenerator& gen;

    void calcFitness();
    void crossPopulation();
    void genRandomPopulation();
    Individual& selectParents();
    Individual& currentIterationBestSolution();
};


#endif //MINIPROJEKT_GENETICALGORITHM_H
//
// Created by Dominik on 02.01.2026.
//

#ifndef MINIPROJEKT_INDIVIDUAL_H
#define MINIPROJEKT_INDIVIDUAL_H
#include <vector>

#include "Evaluator.h"
#include "RandomGenerator.h"


class Individual {
public:
    explicit Individual(const std::vector<int>& genotype);
    Individual(const Individual &other);

    const std::vector<int>& getGenotype() const;
    std::pair<Individual, Individual> cross(const Individual &other, RandomGenerator& generator) const;
    void mutate(double mutProb, RandomGenerator& generator, int numVehicles) ;
    double initFitness(const Evaluator& eval);
    double getFitnes() const;
private:
    std::vector<int> genotype;
    double fitness;

};


#endif //MINIPROJEKT_INDIVIDUAL_H
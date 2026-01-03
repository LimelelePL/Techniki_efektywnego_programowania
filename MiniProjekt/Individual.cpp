//
// Created by Dominik on 02.01.2026.
//

#include "Individual.h"

#include <set>

#include "RandomGenerator.h"

Individual::Individual(const std::vector<int>& genotype) {
    this->genotype = genotype;
    // -1 bo po mutacji/krzyzowaniu zmieniamy fitness
    this-> fitness = -1;
}

Individual::Individual(const Individual &other) {
    this -> genotype = other.genotype;
    this -> fitness = other.fitness;
}

// toDO: zastanowic sie nad tym
double Individual::initFitness(const Evaluator &eval) {
    fitness = eval.evaluate(genotype);
    return fitness;
}

// decyzja o tym czy krzyzowac czy nie bedzie w geneticAlgotirthm
std::pair<Individual, Individual> Individual::cross(const Individual &other) const {
    RandomGenerator generator;
    int size = static_cast<int>(genotype.size());
    int cutPoint =generator.nextInt(1,size-1);

    Individual child1(*this);
    Individual child2(other);

    //wymiana genotypow od punktu przecieciecia
    for (int i = cutPoint; i<size; i++) {
        child1.genotype[i] = other.genotype[i];
        child2.genotype[i] = this->genotype[i];
    }

    // po modyfikacji genotypów należy ponownie policzyc funkcje przystosowania
    child1.fitness = -1;
    child2.fitness = -1;

    return {child1, child2};
}

void Individual::mutate(double mutProb, RandomGenerator& generator) {
    // wybieramy unikalne geny
    std::set<int> uniqueGenes(genotype.begin(), genotype.end());
    std::vector<int> availableGenes(uniqueGenes.begin(), uniqueGenes.end());

    for (int & i : genotype) {
        // mutuje tylko ten gen który spełnia warunek p<=mutProb
        bool shouldMutate = generator.nextDouble(0,1) <= mutProb;
        if (shouldMutate) {
            int newGen = availableGenes[generator.nextInt(0,static_cast<int>(availableGenes.size())-1)];
            i = newGen;
            // po zmianie choc jednego genu przystosowanie musi byc obliczone ponownie
            this->fitness = -1;
        }
    }
}

const std::vector<int> &Individual::getGenotype() const {
    return genotype;
}

double Individual::getFitnes() {
    return fitness;
}



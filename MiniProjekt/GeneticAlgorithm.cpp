//
// Created by Dominik on 02.01.2026.
//

#include "GeneticAlgorithm.h"

#include <iostream>

GeneticAlgorithm::GeneticAlgorithm(Evaluator &eval,int popSize, double crossProb, double mutProb, int maxIterations) : crossProb(
    crossProb), mutProb(mutProb), maxIterations(maxIterations), bestSolution(nullptr), eval(eval) {

    if (popSize < 2) {
        this->popSize = 10;
    } else {
        this->popSize = popSize;
    }
}

GeneticAlgorithm::~GeneticAlgorithm() {
    delete bestSolution;
}

void GeneticAlgorithm::run() {
    //generujemy popsize gotowych rozwiazan
    genRandomPopulation();

    for (int i = 0; i < maxIterations; i++) {

        // krzyzowanie ustawia fitness krzyzowanych na -1
        crossPopulation();

        for (Individual &in: population) {
            in.mutate(mutProb, gen, eval.getNumVehicles()); // mutacja tez na -1
        }

        calcFitness();

        Individual &currentBest = currentIterationBestSolution();
        if (bestSolution == nullptr || currentBest.getFitnes() > bestSolution->getFitnes()) {
            delete bestSolution;
            bestSolution = new Individual(currentBest);
        }

    }
}


void GeneticAlgorithm::crossPopulation() {
    vector<Individual> newPopulation;

    while (newPopulation.size() < popSize){
        double prob = gen.nextDouble(0,1);

        Individual& parent1 = selectParents();
        Individual& parent2 = selectParents();

        if (prob > crossProb) {
            newPopulation.push_back(parent1);
            newPopulation.push_back(parent2);
        } else {
            pair<Individual,Individual> crossed = parent1.cross(parent2, gen);

            // dodajemy do nowej populacji
            newPopulation.push_back(crossed.first);
            newPopulation.push_back(crossed.second);
        }
    }

    // gdyby przekroczylo popsize
    if (newPopulation.size() > popSize) {
        newPopulation.pop_back();
    }

    this->population = std::move(newPopulation);

}

void GeneticAlgorithm::genRandomPopulation() {
    const int numVehicles = eval.getNumVehicles();
    const int numClients = eval.getNumClients();

    for (int i = 0; i<popSize; i++) {
        std::vector<int> randGenotype;
        // genotyp to ilosc klientow
        for (int j = 0; j<numClients; j++) {
            // losujemy pojazd
            int gene = gen.nextInt(0,numVehicles-1);
            randGenotype.push_back(gene);
        }
        Individual individual(randGenotype);
        individual.initFitness(eval);
        population.push_back(individual);
    }
    calcFitness();
}

Individual& GeneticAlgorithm::selectParents() {
    //losujemy 1 kandyata
    int bestIdx = gen.nextInt(0, popSize - 1);

    int minSize = 2;
    int optimalSize = 5;

    if (optimalSize > popSize) optimalSize = minSize;

    // Losujemy resztę zawodników turnieju (tutaj 4)
    for (int i = 1; i < optimalSize; i++) {
        int contenderIdx = gen.nextInt(0, popSize - 1);

        if (population[contenderIdx].getFitnes() > population[bestIdx].getFitnes()) {
            bestIdx = contenderIdx;
        }
    }
    return population[bestIdx];
}

Individual& GeneticAlgorithm::currentIterationBestSolution() {
    double bestFitness = -1;
    int bestIndex = 0;

    for (int i = 0; i<popSize; i++) {

        Individual& in = population[i];
        double inFitness = in.getFitnes();

        if (inFitness>=0 && inFitness >= bestFitness) {
            bestFitness = inFitness;
            bestIndex = i;
        }
    }

    return population[bestIndex];
}

void GeneticAlgorithm::calcFitness() {
    for (Individual &in: population) {
        if (in.getFitnes() < 0) {
            in.initFitness(eval);
        }
    }
}

void GeneticAlgorithm::printBest() {
    if (bestSolution) {
        std::cout << "Najlepszy znaleziony dystans: " << 1.0 / bestSolution->getFitnes() << std::endl;
    }
}



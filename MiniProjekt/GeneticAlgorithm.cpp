//
// Created by Dominik on 02.01.2026.
//

#include "GeneticAlgorithm.h"

#include <iostream>

GeneticAlgorithm::GeneticAlgorithm(Evaluator &eval,int popSize, double crossProb, double mutProb, int maxIterations):
     crossProb(crossProb), mutProb(mutProb), maxIterations(maxIterations), eval(eval){

    if (popSize < 2) {
        std::cerr << " populacja musi mieć co najmniej 2 osobników! Ustawiam 10." << std::endl;
        this->popSize = 10;
    } else {
        this->popSize = popSize;
    }

}

void GeneticAlgorithm::run() {
    //generujemy popsize gotowych rozwiazan
    genRandomPopulation();
    for (int i = 0; i<maxIterations; i++) {
        //dla kazdego z nich obliczamy fitness
        for (Individual in : population) {
            if (in.getFitnes()<0) {
                in.initFitness(eval);
            }
        }
        // wykonujemy krzyzowanie
        crossPopulation();
        // mutacja
        for (Individual in : population) {
                in.mutate(mutProb, gen);
        }
    }

    // toDO: pobieramy najlepsze rozwiazanie

}

void GeneticAlgorithm::crossPopulation() {
    vector<Individual> newPopulation;
    int newPopsize = 0;

    while (newPopsize < popSize){
        double prob = gen.nextDouble(0,1);

        Individual& parent1 = selectParents();
        Individual& parent2 = selectParents();

        if (prob > crossProb) {
            newPopulation.push_back(parent1);
            newPopulation.push_back(parent2);
        } else {
            pair<Individual,Individual> crossed = parent1.cross(parent2);
            newPopulation.push_back(crossed.first);
            newPopulation.push_back(crossed.second);
        }
        newPopsize+=2;
    }

    // gdyby przekroczylo popsize
    if (newPopsize > popSize) {
        newPopulation.pop_back();
    }

    this->population = std::move(newPopulation);

}



void GeneticAlgorithm::genRandomPopulation() {
    int numVehicles = eval.getNumVehicles();
    int numClients = eval.getNumClients();

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



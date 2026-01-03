#include <iostream>
#include <iostream>
#include <string>
#include "Evaluator.h"
#include "GeneticAlgorithm.h"

void manualTest() {
    std::string folder = "Vrp-Set-A";
    std::string file = "A-n31-mojTest";


    Evaluator evaluator;
    std::cout << "Laduje problem: " << file << "..." << std::endl;

    if (!evaluator.loadFromFile(folder, file)) {
        std::cerr << "nie udalo sie zaladowac pliku " << std::endl;
    }

    std::vector<int> testGenotype = {0, 1, 0};

    Individual ind(testGenotype);
    double fitness = ind.initFitness(evaluator);
    std::cout << "Mianownik (Dystans + Kara): " << 1.0 / fitness << std::endl;
    std::cout << "Oczekiwany wynik: 5020" << std::endl;
}

int main() {

    // std::string folder = "Vrp-Set-A";
    // std::string file = "A-n32-k5";
    //
    // Evaluator evaluator;
    // std::cout << "Laduje problem: " << file << "..." << std::endl;
    //
    // if (!evaluator.loadFromFile(folder, file)) {
    //     std::cerr << "nie udalo sie zaladowac pliku " << std::endl;
    //     return 1;
    // }
    //
    // int populationSize = 100;
    // double crossoverProbability = 0.8;
    // double mutationProbability = 0.05;
    // int iterations = 10000;
    //
    // GeneticAlgorithm ga(evaluator, populationSize, crossoverProbability, mutationProbability, iterations);
    //
    // std::cout << "Rozpoczynam ewolucje!" << std::endl;
    // ga.run();
    //
    // std::cout << "\n=== WYNIK KONCOWY ===" << std::endl;
    // ga.printBest();

    manualTest();
    return 0;
}

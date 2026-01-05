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

    std::string folder = "Vrp-Set-X";
    std::string file = "X-n209-k16";

    Evaluator evaluator;

    if (!evaluator.loadFromFile(folder, file)) {
        std::cerr << "nie udalo sie zaladowac pliku lub zawiera błąd w dancyh " << std::endl;
        return 1;
    }
    std::cout << "Laduje problem: " << file << "..." << std::endl;

    int populationSize = 1000;
    double crossoverProbability = 0.8;
    double mutationProbability = 0.03;
    int iterations = 5000;
    RandomGenerator generator;

    GeneticAlgorithm ga(evaluator, generator, populationSize, crossoverProbability, mutationProbability, iterations);

    std::cout << "Rozpoczynam ewolucje!" << std::endl;
    ga.run();

    std::cout << "\n=== WYNIK KONCOWY ===" << std::endl;
    ga.printBest();
    ga.printDetailedBest();

    //manualTest();
    return 0;
}

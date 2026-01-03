//
// Created by Dominik on 02.01.2026.
//

#include "Evaluator.h"

#include <algorithm>
#include <chrono>

Evaluator::Evaluator() {
    numVehicles = 0;
}

bool Evaluator::loadFromFile(const std::string &folder, const std::string &name) {
    ProblemLoader loader(folder, name);
    data = loader.LoadProblem();

    //sprawdzamy czy dane zaladowane do data maja sens (stala WrongValue = -1)
    if (data.GetDimension() <= 0 || data.GetCapacity() <= 0) {
        return false;
    }
    numVehicles = data.GetDimension() - 1;

    return true;
    //PAMIETAC ZEBY OBSLUZYC W INTERFEJSIE
}

double Evaluator::evaluate(const std::vector<int>& genotype) const {
    //numVehicles = *ranges::max_element(genotype)+1;

    int maxCapacity = data.GetCapacity();
    // w pliku indeksowanie jest od 1
    int depot = data.GetDepot() - 1;

    vector<int> demands = data.GetDemands();
    vector<int> permutation = data.GetPermutation();
    vector<int> loads(numVehicles,0);
    vector<int> distances(numVehicles,0);
    vector<int> lastCustomerOfVehicle(numVehicles, depot);

    //toDo: do obsluzenia
    if (genotype.size()!=permutation.size()) return -1;

    for (int i = 0; i<permutation.size(); i++) {
        // przyporządkowujemy klientowi pojazd ktory odpowiada mu w genotypie
        int clientID = permutation[i] - 1;
        int vehicleID = genotype[i];

        distances[vehicleID] += data.CalculateDistance(lastCustomerOfVehicle[vehicleID], clientID);
        loads[vehicleID] += demands[clientID];
        lastCustomerOfVehicle[vehicleID] = clientID;
    }

    // obliczamy wartość naszej funkcji przystosowania
    int totalDist = 0;
    int totalPenalty = 0;
    for (int i = 0; i<numVehicles; i++) {
        if (lastCustomerOfVehicle[i] != depot) {
            // jezeli samochód został użyty musi jeszcze wrócic do bazy
            totalDist += distances[i] + data.CalculateDistance(lastCustomerOfVehicle[i], depot);
        }

        if (loads[i] > maxCapacity) {
            constexpr int penalty = 1000;
            // kara penalty za każdą nadmiarową jednostkę towaru
            totalPenalty += (loads[i] - maxCapacity) * penalty;
        }
    }

    return 1/(totalDist+totalPenalty);
}

int Evaluator::getNumVehicles() const {
    return numVehicles;
}

int Evaluator::getNumClients() const {
    return data.GetNumCustomers();
}






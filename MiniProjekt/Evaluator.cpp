//
// Created by Dominik on 02.01.2026.
//

#include "Evaluator.h"

#include <algorithm>
#include <chrono>
using namespace std;

#include "ConstantValues.h"

Evaluator::Evaluator() {
    this->numVehicles = DEFAULT_NUMVEHICLES;
}

Result<void,Error> Evaluator::loadFromFile(const std::string &folder, const std::string &name) {
    InstanceReader loader(folder, name);

    auto loadResult = loader.readInstance();

    if (!loadResult.isSuccess()) return Result<void, Error>::fail(loadResult.getErrors());

    this->data = loadResult.getValue();

    if (data.getTotalNodes() <= 0)
        return Result<void, Error>::fail(new Error("INVALID_DIMENSION"));
    if (data.getFleetSize() <= 0)
        return Result<void, Error>::fail(new Error("INVALID_NUM_GROUPS"));
    if (data.getCapacityLimit() <= 0)
        return Result<void, Error>::fail(new Error("INVALID_CAPACITY"));
    if (!checkIfProblemIsSolvable())
        return Result<void, Error>::fail(new Error("PROBLEM_UNSOLVABLE"));


    numVehicles = getNumClients();
    return Result<void, Error>::ok();
}

Result<double, Error> Evaluator::evaluate(const std::vector<int>& genotype) const {
    int maxCapacity = data.getCapacityLimit();  // ← POPRAWKA!
    int depot = data.getDepotNode() - 1;
    int numClients = data.getCustomerCount();

    vector<int> demands = data.getDemands();
    vector<int> permutation = data.getVisitOrder();
    vector<int> loads(numVehicles, 0);
    vector<double> distances(numVehicles, 0.0);
    vector<int> lastCustomerOfVehicle(numVehicles, depot);

    if (genotype.size() != permutation.size())
        return Result<double, Error>::fail(new Error("GENOTYPE_MISMATCH"));

    // Grupowanie: klient -> pojazd
    vector<vector<int>> groups(numVehicles);
    for (int client = 0; client < numClients; client++) {
        int vehicle = genotype[client];
        groups[vehicle].push_back(client);
    }

    double totalDist = 0;
    int totalPenalty = 0;

    for (int v = 0; v < numVehicles; v++) {

        int load = 0;
        int last = depot;
        bool used = false;

        for (int p : permutation) {
            // pomijamy magazyn
            if (p == data.getDepotNode()) {
                continue;
            }
            // czy klient z permutacji nalezy do grupy ktora oblsuguje samochod v
            int client = p-1;
            if (genotype[client] == v) {
                totalDist += data.calculateDistance(last, client);
                load += demands[client];
                last = client;
                used = true;
            }
        }

        if (used) {
            totalDist += data.calculateDistance(last, depot);
        }
        if (load > maxCapacity) {
            constexpr int penalty = 1000;
            totalPenalty += (load - maxCapacity) * penalty;
        }

    }

    double fitness = 1.0 / (totalDist + totalPenalty);
    return Result<double, Error>::ok(fitness);
}

// zwraca false gdy dany demand z pliku bedzie wiekszy od capacity
bool Evaluator::checkIfProblemIsSolvable() {
    int cap = data.getCapacityLimit();
    const std::vector<int>& demands = data.getDemands();

    for (int d : demands) {
        if (d > cap) {
            return false;
        }
    }
    return true;
}

int Evaluator::getNumVehicles() const {
    return numVehicles;
}

int Evaluator::getNumClients() const {
    return data.getCustomerCount();
}





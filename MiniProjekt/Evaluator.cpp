//
// Created by Dominik on 02.01.2026.
//

#include "Evaluator.h"

#include <algorithm>
#include <chrono>
#include <iostream>
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


    numVehicles = data.getFleetSize();

    return Result<void, Error>::ok();
}

Result<double, Error> Evaluator::evaluate(const std::vector<int>& genotype) const {
    int maxCapacity = data.getCapacityLimit();
    int depot = data.getDepotNode() - 1; // Indeks bazy 0
    const vector<int>& demands = data.getDemands();
    const vector<int>& permutation = data.getVisitOrder();

    vector<int> loads(numVehicles, 0);
    vector<double> distances(numVehicles, 0.0);
    vector<int> lastPos(numVehicles, depot);
    vector<bool> used(numVehicles, false);

    for (int p : permutation) {
        if (p == data.getDepotNode()) continue;

        int clientDistIdx = p - 1; // Indeks do tablicy dystansów 0-based
        int genotypeIdx = p - 2; // po id: Klient nr 2 to gen[0]
        int v = genotype[genotypeIdx]; // Pobieramy przypisany pojazd

        if (v >= 0 && v < numVehicles) {
            distances[v] += data.calculateDistance(lastPos[v], clientDistIdx);
            loads[v] += demands[clientDistIdx];
            lastPos[v] = clientDistIdx;
            used[v] = true;
        }
    }

    double totalDist = 0;
    long totalPenalty = 0;
    for (int v = 0; v < numVehicles; v++) {
        if (used[v]) totalDist += distances[v] + data.calculateDistance(lastPos[v], depot);
        if (loads[v] > maxCapacity) totalPenalty += (loads[v] - maxCapacity) * 100;
    }

    return Result<double, Error>::ok(1.0 / (totalDist + (double)totalPenalty));
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





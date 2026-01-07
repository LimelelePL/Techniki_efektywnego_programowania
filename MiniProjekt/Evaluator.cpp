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


    numVehicles = data.getFleetSize();
    return Result<void, Error>::ok();
}

Result<double, Error> Evaluator::evaluate(const std::vector<int>& genotype) const {
    int maxCapacity = data.getCapacityLimit();  // ← POPRAWKA!
    int depot = data.getDepotNode() - 1;

    vector<int> demands = data.getDemands();
    vector<int> permutation = data.getVisitOrder();
    vector<int> loads(numVehicles, 0);
    vector<double> distances(numVehicles, 0.0);
    vector<int> lastCustomerOfVehicle(numVehicles, depot);

    if (genotype.size() != permutation.size())
        return Result<double, Error>::fail(new Error("GENOTYPE_MISMATCH"));

    for (size_t i = 0; i < permutation.size(); i++) {
        int clientID = permutation[i] - 1;
        int vehicleID = genotype[i];

        distances[vehicleID] += data.calculateDistance(lastCustomerOfVehicle[vehicleID], clientID);
        loads[vehicleID] += demands[clientID];
        lastCustomerOfVehicle[vehicleID] = clientID;
    }

    double totalDist = 0;
    int totalPenalty = 0;

    for (int i = 0; i < numVehicles; i++) {
        if (lastCustomerOfVehicle[i] != depot) {
            totalDist += distances[i] + data.calculateDistance(lastCustomerOfVehicle[i], depot);
        }

        if (loads[i] > maxCapacity) {
            constexpr int penalty = 1000;
            totalPenalty += (loads[i] - maxCapacity) * penalty;
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





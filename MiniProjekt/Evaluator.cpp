//
// Created by Dominik on 02.01.2026.
//

#include "Evaluator.h"

#include <algorithm>
#include <chrono>

#include "ConstantValues.h"

Evaluator::Evaluator() {
    this->numVehicles = DEFAULT_NUMVEHICLES;
}

Result<void,Error> Evaluator::loadFromFile(const std::string &folder, const std::string &name) {
    ProblemLoader loader(folder, name);

    auto loadResult = loader.LoadProblem();

    if (!loadResult.isSuccess()) return Result<void, Error>::fail(loadResult.getErrors());

    this->data = loadResult.getValue();
    
    if (data.GetDimension() <= 0)
        return Result<void, Error>::fail(new Error("INVALID_DIMENSION"));
    if (data.GetNumGroups() <= 0)
        return Result<void, Error>::fail(new Error("INVALID_NUM_GROUPS"));
    if (data.GetCapacity() <= 0)
        return Result<void, Error>::fail(new Error("INVALID_CAPACITY"));
    if (!checkIfProblemIsSolvable())
        return Result<void, Error>::fail(new Error("PROBLEM_UNSOLVABLE"));


    numVehicles = data.GetNumGroups();
    return Result<void, Error>::ok();
}

Result<double, Error> Evaluator::evaluate(const std::vector<int>& genotype) const {

    int maxCapacity = data.GetCapacity();
    // w pliku indeksowanie jest od 1
    int depot = data.GetDepot() - 1;

    vector<int> demands = data.GetDemands();
    vector<int> permutation = data.GetPermutation();
    vector<int> loads(numVehicles,0);
    vector<double> distances(numVehicles,0);
    vector<int> lastCustomerOfVehicle(numVehicles, depot);

    //toDo: do obsluzenia
    if (genotype.size()!=permutation.size()) return Result<double, Error>(new Error("GENOTYPE_MISMATCH"));


    for (int i = 0; i<permutation.size(); i++) {
        // przyporządkowujemy klientowi pojazd ktory odpowiada mu w genotypie
        int clientID = permutation[i] - 1;
        int vehicleID = genotype[i];

        distances[vehicleID] += data.CalculateDistance(lastCustomerOfVehicle[vehicleID], clientID);
        loads[vehicleID] += demands[clientID];
        lastCustomerOfVehicle[vehicleID] = clientID;
    }

    // obliczamy wartość naszej funkcji przystosowania
    double totalDist = 0;
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
    double fitness = 1.0 / (totalDist + totalPenalty);
    return Result<double, Error>::ok(fitness);
}

// zwraca false gdy dany demand z pliku bedzie wiekszy od capacity
bool Evaluator::checkIfProblemIsSolvable() {
    int cap = data.GetCapacity();
    const std::vector<int>& demands = data.GetDemands();

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
    return data.GetNumCustomers();
}






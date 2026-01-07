//
// Created by Dominik on 02.01.2026.
//

#ifndef MINIPROJEKT_EVALUATOR_H
#define MINIPROJEKT_EVALUATOR_H
#include "InstanceReader.hpp"
#include "Errors/Error.h"
#include "Errors/Result.h"
using namespace std;

class Evaluator {
public:
    Evaluator();

    [[nodiscard]] Result<double, Error> evaluate(const std::vector<int> &genotype) const;
    Result<void, Error> loadFromFile(const std::string& folder, const std::string& name);
    [[nodiscard]] int getNumVehicles() const;
    [[nodiscard]] int getNumClients() const;

    [[nodiscard]] std::vector<int> getDemands() const { return data.getDemands(); }

    [[nodiscard]] std::vector<int> getPermutation() const { return data.getVisitOrder();}

    [[nodiscard]] int getCapacity() const { return data.getCapacityLimit(); }


private:
    VrpInstance data;
    int numVehicles;

    bool checkIfProblemIsSolvable();

};


#endif //MINIPROJEKT_EVALUATOR_H
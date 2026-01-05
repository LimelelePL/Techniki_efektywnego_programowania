//
// Created by Dominik on 02.01.2026.
//

#ifndef MINIPROJEKT_EVALUATOR_H
#define MINIPROJEKT_EVALUATOR_H
#include "ProblemLoader.hpp"
using namespace LcVRPContest;

class Evaluator {
public:
    Evaluator();

    double evaluate(const std::vector<int> &genotype) const;
    bool loadFromFile(const std::string& folder, const std::string& name);
    int getNumVehicles() const;
    int getNumClients() const;

    std::vector<int> getDemands() const { return data.GetDemands(); }

    std::vector<int> getPermutation() const { return data.GetPermutation(); }

    int getCapacity() const { return data.GetCapacity(); }


private:
    ProblemData data;
    int numVehicles;

    bool checkIfProblemIsSolvable();

};


#endif //MINIPROJEKT_EVALUATOR_H
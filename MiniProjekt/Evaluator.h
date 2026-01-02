//
// Created by Dominik on 02.01.2026.
//

#ifndef MINIPROJEKT_EVALUATOR_H
#define MINIPROJEKT_EVALUATOR_H
#include "Individual.h"
#include "ProblemLoader.hpp"
using namespace LcVRPContest;

class Evaluator {
public:
    Evaluator();
    double evaluate(const std::vector<int> &genotype) const;
    bool loadFromFile(const std::string& folder, const std::string& name);
    int getNumVehicles() const;

private:
    ProblemData data;
    int numVehicles;
};


#endif //MINIPROJEKT_EVALUATOR_H
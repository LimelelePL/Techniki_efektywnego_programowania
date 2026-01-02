//
// Created by Dominik on 02.01.2026.
//

#include "RandomGenerator.h"
#include <algorithm>
#include <random>

RandomGenerator::RandomGenerator()
    : engine(std::random_device{}()) {}

int RandomGenerator::nextInt(int min, int max) {
    if (min > max) std::swap(min, max);
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}

double RandomGenerator::nextDouble(double min, double max) {
    if (min > max) std::swap(min, max);
    std::uniform_real_distribution<double> dist(min, max);
    return dist(engine);
}

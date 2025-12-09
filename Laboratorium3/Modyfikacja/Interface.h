//
// Created by Dominik on 13.11.2025.
//

#ifndef ZADANIE_INTERFACE_H
#define ZADANIE_INTERFACE_H
#include "Tree.h"


class Interface {
public:
    void run();
private:
    Tree tree;
    static void printError(const Result &r);
};


#endif //ZADANIE_INTERFACE_H
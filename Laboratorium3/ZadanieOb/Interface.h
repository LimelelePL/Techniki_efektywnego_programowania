//
// Created by Dominik on 13.11.2025.
//

#ifndef ZADANIEOB_INTERFACE_H
#define ZADANIEOB_INTERFACE_H

#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
using namespace std;

#include "Tree.h"
#include "Parser.h"
#include "Error.h"

/*
 * Interfejs użytkownika – w pełni obiektowy.
 * Obsługa komend:
 * enter <expr>
 * print
 * vars
 * comp <values...>
 * join <expr>
 * exit
 */
class Interface {
private:
    Tree tree;

public:
    void run();    // główna pętla poleceń
};

#endif


#endif //ZADANIEOB_INTERFACE_H
//
// Created by Dominik on 13.11.2025.
//

#ifndef ZADANIE_TYPE_H
#define ZADANIE_TYPE_H



#include "Parser.h"
#include "Node.h"


class TypeChecker {
public:
    static Type calculateType(std::string &value);
};


#endif //ZADANIE_TYPE_H
//
// Created by Dominik on 13.11.2025.
//

#include "TypeChecker.h"

#include <iostream>

#include "Tree.h"


// metoda sprawdzająca typ operacji z danego stringa
Type TypeChecker::calculateType(std::string &value) {
    if (value.empty()) return UNKNOWN;

    if (value == OP_SIN || value == OP_COS) return UNARY_OP;
    if (value == OP_ADD || value == OP_SUB || value == OP_MUL || value == OP_DIV) return BINARY_OP;

    /* żeby znazwa zmiennej była poprawna to:
     * - musi zawierac co najmniej jedną wielką lub małą literę
     * - nie może zawierać znaków specjalnych
     * - może zawierać liczbę, jeżeli zawiera co najmniej jedną litere
     */

    // nazwa zmiennej przed naprawą
    string before = value;

    bool containsLetter = Parser::cleanAndValidateVariable(value);

    // nazwa zmiennej po naprawie
    string after = value;

    // jesli wynik ma litere to jest zmienna
    if (containsLetter) {
        return VARIABLE;
    }

    // jeśli po oczyszczeniu wartosc wygląda jak liczba zmieniamy na liczbe
    if (Parser::isValidNumber(value)) {
        return NUMBER;
    }

    return UNKNOWN;
}
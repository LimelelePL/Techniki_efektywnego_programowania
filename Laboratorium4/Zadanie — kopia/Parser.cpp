//
// Created by Dominik on 13.11.2025.
//

#include "Parser.h"

#include "Tree.h"

// dzieli operatory wedlug spacji
vector<string> Parser::split(string formula) {
    vector<string> result;
    string word;

    for (int i = 0; i < formula.length(); i++) {
        if (formula[i] != ' ')
            word += formula[i];
        else if (!word.empty()) {
            result.push_back(word);
            word = "";
        }
    }

    if (!word.empty()) result.push_back(word);
    return result;
}

//sprawdza czy napis jest liczba
bool Parser::isValidNumber(const string &token) {
    if (token.empty()) return false;

    for (char c : token) {
        if (!isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

// sprawdza poprawnosc zmiennej
bool Parser::cleanAndValidateVariable(string &token) {
    string original = token;
    string cleanToken;

    bool containsLetter = false;

    for (int i = 0; i < token.length(); ++i) {
        char c = token[i];

        // litery i cyfry są dozwolone
        if (isalnum(static_cast<unsigned char>(c))) {
            cleanToken += c;
            if (isalpha(c)) containsLetter = true;
        }
    }

    token = cleanToken;

    // jezeli nie ma litery jest niepoprawna
    if (!containsLetter) return false;
    // Nazwa zmiennej nie może być pusta
    return !token.empty();
}

// metoda sprawdzająca typ operacji z danego stringa
Type Parser::calculateType(std::string &value) {
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
    if (isValidNumber(value)) {
        return NUMBER;
    }

    return UNKNOWN;
}

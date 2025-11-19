//
// Created by Dominik on 13.11.2025.
//

#include "Parser.h"

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
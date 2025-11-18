//
// Created by Dominik on 13.11.2025.
//

#ifndef ZADANIEOB_PARSER_H
#define ZADANIEOB_PARSER_H


#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
using namespace std;

/*
 * Klasa odpowiedzialna wyłącznie za przetwarzanie tokenów:
 * - split (dzielenie na tokeny)
 * - walidacja liczb
 * - czyszczenie nazw zmiennych ze znaków niedozwolonych
 */
class Parser {
public:
    static vector<string> split(const string &formula);
    static bool isNumber(const string &token);
    static bool cleanVariable(string &token);
};

#endif


#endif //ZADANIEOB_PARSER_H
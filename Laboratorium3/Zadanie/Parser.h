//
// Created by Dominik on 13.11.2025.
//

#ifndef ZADANIE_PARSER_H
#define ZADANIE_PARSER_H
#include <string>
#include <vector>
using namespace std;


class Parser {
public:
    static bool isValidNumber(const string &token);
    static bool cleanAndValidateVariable(string &token);
    static vector<string> split(string formula);
};


#endif //ZADANIE_PARSER_H
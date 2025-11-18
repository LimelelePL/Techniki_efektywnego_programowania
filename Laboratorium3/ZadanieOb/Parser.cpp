//
// Created by Dominik on 13.11.2025.
//
#include "Parser.h"
#include <cctype>

vector<string> Parser::split(const string &formula) {
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

    if (!word.empty())
        result.push_back(word);

    return result;
}

bool Parser::isNumber(const string &token) {
    if (token.empty()) return false;
    for (char c : token)
        if (!isdigit((unsigned char)c)) return false;
    return true;
}

bool Parser::cleanVariable(string &token) {
    string cleaned;
    bool hasLetter = false;

    for (int i = 0; i < token.length(); i++) {
        char c = token[i];
        if (isalnum((unsigned char)c)) {
            cleaned += c;
            if (isalpha(c)) hasLetter = true;
        }
    }

    token = cleaned;
    return hasLetter && !token.empty();
}

#include "Parser.h"
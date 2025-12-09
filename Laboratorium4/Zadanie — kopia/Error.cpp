//
// Created by Dominik on 27.11.2025.
//
#include <string>

using namespace std;
#include "Error.h"

Error::Error(const string& code) {
    this->code = code;
}

string Error::getCode() const {
    return code;
}




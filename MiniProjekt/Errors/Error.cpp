//
// Created by Dominik on 06.01.2026.
//

#include "Error.h"

#include <string>

using namespace std;
#include "Error.h"

Error::Error(const string& code) {
    this->code = code;
}

string Error::getCode() const {
    return code;
}
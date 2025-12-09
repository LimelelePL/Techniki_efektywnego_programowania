//
// Created by Dominik on 18.11.2025.
//

#ifndef ZADANIE_RESULT_H
#define ZADANIE_RESULT_H


#ifndef RESULT_H
#define RESULT_H

#include <string>
#include "ErrorCode.h"
using namespace std;

class Result {
public:
    Result(ErrorCode c, const std::string &msg);
    ErrorCode getCode() const;
    string getMessage() const;
    static Result success();


private:
    ErrorCode code;
    string message;

};

#endif


#endif //ZADANIE_RESULT_H
//
// Created by Dominik on 06.01.2026.
//

#ifndef MINIPROJEKT_ERROR_H
#define MINIPROJEKT_ERROR_H


#include <string>

class Error {
public:
    explicit Error(const std::string& code);
    std::string getCode() const;

private:
    std::string code;
};


#endif //MINIPROJEKT_ERROR_H
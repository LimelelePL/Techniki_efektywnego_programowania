#ifndef ZADANIE_ERROR_H
#define ZADANIE_ERROR_H

#include <string>

class Error {
public:
    explicit Error(const std::string& code);
    std::string getCode() const;

private:
    std::string code;
};

#endif // ZADANIE_ERROR_H


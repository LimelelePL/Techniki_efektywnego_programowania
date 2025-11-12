// `ComplexNumber.h`
#ifndef MODYFIKACJA_COMPLEXNUMBER_H
#define MODYFIKACJA_COMPLEXNUMBER_H

#include "Number.h"
#include <string>

class ComplexNumber {
public:
    ComplexNumber();
    ComplexNumber(int realPart, int imagPart);
    ComplexNumber(const Number &realPart, const Number &imagPart = Number(0));
    ComplexNumber(const ComplexNumber &other);
    ~ComplexNumber();
    ComplexNumber &operator=(const ComplexNumber &other);

    std::string toString() const;

    ComplexNumber operator+(const ComplexNumber &rhs) const;
    ComplexNumber operator-(const ComplexNumber &rhs) const;
    ComplexNumber operator*(const ComplexNumber &rhs) const;
    ComplexNumber operator/(const ComplexNumber &rhs) const;

    ComplexNumber operator+(const Number &rhs) const;
    ComplexNumber operator*(const Number &rhs) const;

    ComplexNumber operator~() const;

private:
    Number real;
    Number imag;
};

std::ostream &operator<<(std::ostream &os, const ComplexNumber &c);
ComplexNumber operator+(const Number &lhs, const ComplexNumber &rhs);
ComplexNumber operator*(const Number &lhs, const ComplexNumber &rhs);

#endif //MODYFIKACJA_COMPLEXNUMBER_H



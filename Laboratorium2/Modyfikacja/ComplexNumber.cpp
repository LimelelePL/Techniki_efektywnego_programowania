// cpp
#include "ComplexNumber.h"
#include <string>

ComplexNumber::ComplexNumber() {
    // domyślne konstruktory Number zostaną wywołane automatycznie
}

ComplexNumber::ComplexNumber(int realPart, int imagPart) {
    real = Number(realPart);
    imag = Number(imagPart);
}

ComplexNumber::ComplexNumber(const Number &realPart, const Number &imagPart) {
    real = realPart;
    imag = imagPart;
}

ComplexNumber::ComplexNumber(const ComplexNumber &other) {
    real = other.real;
    imag = other.imag;
}

ComplexNumber::~ComplexNumber() {
    //number ma wlasny destruktor
}

ComplexNumber &ComplexNumber::operator=(const ComplexNumber &other) {
    if (this == &other) return *this;
    real = other.real;
    imag = other.imag;
    return *this;
}

std::string ComplexNumber::toString() const {
    std::string r = real.toString();
    std::string i = imag.toString();
    if (!i.empty() && i[0] == '-') return r + " - " + i.substr(1) + "i";
    return r + " + " + i + "i";
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber &rhs) const {
    ComplexNumber res;
    res.real = real + rhs.real;
    res.imag = imag + rhs.imag;
    return res;
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber &rhs) const {
    ComplexNumber res;
    res.real = real - rhs.real;
    res.imag = imag - rhs.imag;
    return res;
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber &rhs) const {
    ComplexNumber res;
    Number ac = real * rhs.real;
    Number bd = imag * rhs.imag;
    Number ad = real * rhs.imag;
    Number bc = imag * rhs.real;
    res.real = ac - bd;
    res.imag = ad + bc;
    return res;
}

ComplexNumber ComplexNumber::operator/(const ComplexNumber &rhs) const {
    ComplexNumber res;
    Number c2 = rhs.real * rhs.real;
    Number d2 = rhs.imag * rhs.imag;
    Number denom = c2 + d2;
    Number ac = real * rhs.real;
    Number bd = imag * rhs.imag;
    Number realNum = ac + bd;
    Number bc = imag * rhs.real;
    Number ad = real * rhs.imag;
    Number imagNum = bc - ad;
    res.real = realNum / denom;
    res.imag = imagNum / denom;
    return res;
}

//  (a+bi) + (0 + rhs i) = a + (b + rhs) i
ComplexNumber ComplexNumber::operator+(const Number &rhs) const {
    ComplexNumber res;
    res.real = real;
    res.imag = imag + rhs;
    return res;
}

// (a+bi) * (0 + rhs i) = (-b*rhs) + (a*rhs) i
ComplexNumber ComplexNumber::operator*(const Number &rhs) const {
    ComplexNumber res;
    Number p = imag * rhs;
    Number realPart = Number(0) - p;
    Number imagPart = real * rhs;
    res.real = realPart;
    res.imag = imagPart;
    return res;
}
ComplexNumber ComplexNumber::operator~() const {
    ComplexNumber res(*this);
    res.imag = Number(0) - imag;
    return res;
}

std::ostream & operator<<(std::ostream &os, const ComplexNumber &c) {
   
}

ComplexNumber operator+(const Number &lhs, const ComplexNumber &rhs) {
    return ComplexNumber(lhs, Number(0)) + rhs;
}

ComplexNumber operator*(const Number &lhs, const ComplexNumber &rhs) {
    return ComplexNumber(lhs, Number(0)) * rhs;
}





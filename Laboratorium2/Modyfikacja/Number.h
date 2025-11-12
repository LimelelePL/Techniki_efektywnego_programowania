// cpp
#ifndef MODYFIKACJA_NUMBER_H
#define MODYFIKACJA_NUMBER_H

#include <string>

const static int DEFAULT_LENGTH = 10;
const static int DEFAULT_VALUE = 1;
const static int BASE = 10;

class Number {
public:
    Number();
    ~Number();
    Number(int value);
    Number(int length, int initialValue);
    Number(const Number &pOther);

    std::string toString() const;

    Number &operator =(const int value);
    Number operator +(const Number &pOther) const;
    Number operator -(const Number &pOther) const;

    int compareTo(const Number &pOther) const;

    Number operator *(const Number &pOther) const;
    Number operator /(const Number &pOther) const;
    Number &operator=(const Number &pOther); // zwraca referencję

    void printNumber() const;
    void initializeArray(int value);
    static int calculateLength(int val);
    void checkNegative (int &val);

private:
    int *array;
    int length;
    bool isNegative;
};

#endif //MODYFIKACJA_NUMBER_H

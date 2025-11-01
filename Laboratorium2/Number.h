//
// Created by Dominik on 30.10.2025.
//

#ifndef LABORATORIUM2_NUMBER_H
#define LABORATORIUM2_NUMBER_H
#include <string>

const static int DEFAULT_LENGTH = 10;
const static int DEFAULT_VALUE = 1;

class Number {
public:
Number();
~Number();
Number(int value);
    Number(int length, int initialValue);
Number(const Number &pOther);

std::string toString();

Number &operator =(const int value);
Number operator +(const Number &pOther);
Number operator -(const Number &pOther);

int compareTo(const Number &pOther) const;

Number operator *(const Number &pOther);
Number operator /(const Number &pOther);
void operator=(const Number &pOther);


void printNumber() const;
void initializeArray(int value);
static int calculateLength(int val);
void checkNegative (int &val);



private:
    int *array;
    int length;
    bool isNegative;

};


#endif //LABORATORIUM2_NUMBER_H
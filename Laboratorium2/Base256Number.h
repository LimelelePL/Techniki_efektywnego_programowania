//
// Created by Dominik on 04.11.2025.
//

#ifndef LABORATORIUM2_BASE256NUMBER_H
#define LABORATORIUM2_BASE256NUMBER_H
#include <string>

const int BASE_NUMBER= 256;
const int DEFAULT_VAL = 0;
const int DEFAULT_LEN = 0;

class Base256Number {
public:
    Base256Number();
    Base256Number(const Base256Number &other);
    ~Base256Number();

    Base256Number& operator = (const Base256Number &other);
    void operator = (const int value);

    void initializeArray(int value) const;
    int calculateLength(int value);
    void printNumber();
    std::string toHexString();
    std::string convertToHex(unsigned char val);



private:
    unsigned char* array;
    int length;
};


#endif //LABORATORIUM2_BASE256NUMBER_H
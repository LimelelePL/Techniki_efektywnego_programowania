//
// Created by Dominik on 04.11.2025.
//

#include "Base256Number.h"

#include <iostream>
#include <ratio>
using namespace std;

Base256Number::Base256Number() {
    length = DEFAULT_LEN;
    array = new unsigned char[length];

    for (int i = 0; i < length; i++) {
        array[i] = DEFAULT_VAL;
    }
}

Base256Number::~Base256Number() {
    delete []array;
}

Base256Number::Base256Number(const Base256Number &other) {
    length = other.length;
    array = new unsigned char[length];
    for (int i = 0; i < length; i++) array[i] = other.array[i];
}

Base256Number & Base256Number::operator=(const Base256Number &other) {
    delete[] array;
    length = other.length;
    array = new unsigned char [length];
   for (int i = 0; i < length; i++)
       array[i] = other.array[i];

    return *this;
}

void Base256Number::operator=(const int value) {

    int val = value;
    delete []array;

    length = calculateLength(value);
    array = new unsigned char[length];
    initializeArray(value);
}


int Base256Number :: calculateLength(int value) {
    int len = 0;
    if (value < BASE_NUMBER) return 1;

    while (value>0) {
        value = value/BASE_NUMBER;
        len++;
    }
    return len;
}



void Base256Number::initializeArray(int value) const {
    if (value == 0) {
        array[0] = 0;
        return;
    }

    for (int i = 0; i < length; i++) {
        array[length - i - 1] = value % BASE_NUMBER;
        value = value / BASE_NUMBER;
    }
}

void Base256Number::printNumber() {
    for (int i = 0; i < length; i++) {
        std::cout << static_cast<int>(array[i]) << " ";
    }
    std::cout << std::endl;
}

std::string Base256Number::convertToHex(unsigned char value) {
    int decimal = value;

    string hex = "";

    while (decimal>0) {

        int rest  = decimal%16;

        if (rest <= 16) {

            if (rest<9) {
                hex += '0' + rest;
            } else {
                rest = rest-10;
                hex += 'A' + rest;
            }
        }

        decimal = decimal/16;
    }
    return  hex;
}


std::string Base256Number::toHexString() {
    string result = "0x";
    for (int i = 0; i<length; i++ ) {
        result += convertToHex(array[i]);
    }
    return result;
}


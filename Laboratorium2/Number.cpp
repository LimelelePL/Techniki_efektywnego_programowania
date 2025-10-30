//
// Created by Dominik on 30.10.2025.
//

#include "Number.h"

#include <iostream>
using namespace std;

Number::Number() {
    length = DEFAULT_LENGTH;
    array = new int[length];
    isNegative = false;

    for (int i=0; i<length; i++) {
        array[i] = DEFAULT_VALUE;
    }
}

//poprawic len na number
Number::Number(int value) {
    isNegative = false;
    checkNegative(value);
    length = calculateLength(value);
    array = new int[length];

    initializeArray(value);
}

Number::Number(const Number &pOther) {
    if (pOther.array != nullptr) {
        isNegative = pOther.isNegative;
        length = pOther.length;
        array = new int[length];

        for (int i = 0; i<pOther.length; i++) {
            array[i] = pOther.array[i];
        }
    } else {
        isNegative = false;
        length = 0;
        array = nullptr;
    }
}

//moze sprawdzic czy value nie jest jakas pojebanie duza liczba?
Number& Number::operator=(const int value) {
    delete []array;
    int valueCopy = value;

    checkNegative(valueCopy);
    length = calculateLength(valueCopy);
    array = new int[length];

    initializeArray(valueCopy);
    return *this;
}

Number::~Number() {
    delete []array;

}


void Number::printNumber() const {
    if (isNegative) cout<<"- ";
    for (int i = 0; i<length; i++) {
        cout<<array[i]<<" ";
    }
}


void Number::initializeArray(int value) {

    if (value == 0) {
        array[0] = 0;
        return;
    }

    for (int i = 0; i<length; i++) {
        array[length-i-1] = value%10;
        value = value/10;
    }
}

int Number::calculateLength(int val) {
    if (val<0) val= -val;
    int len = 0;

    if (val == 0) return 1;

    while (val > 0 ) {
        val /= 10;
        len++;
    }
    cout<<"dlugosc " << len << endl;
    return len;
}

void Number::checkNegative(int &val) {
    if (val<0) {
        isNegative = true;
        val = -val;
    }
}



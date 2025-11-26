#include <iostream>

#include "ComplexNumber.h"

int main() {
    ComplexNumber num1(0,1);
    ComplexNumber num2(0,1);
    ComplexNumber result = num1*num2;

    std::cout << result.toString();
}
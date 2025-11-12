#include <iostream>

#include "ComplexNumber.h"
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    ComplexNumber num1(0,1);
    ComplexNumber num2(0,1);
    ComplexNumber result = num1*num2;

    std::cout << result.toString();
}
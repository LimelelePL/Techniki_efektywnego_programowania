#include <iostream>
#include "Union.h"

int main() {
    Union<int, double> u(5);
    std::cout << std::boolalpha;
    std::cout << "isFirst: " << u.isFirst() << ", value: " << u.getFirst() << std::endl;

    u = 4.0;
    std::cout << "isSecond: " << u.isSecond() << ", value: " << u.getSecond() << std::endl;

    int x = 10;
    double y = 3.14;
    Union<int *, double *> ptrUnion(&x);
    std::cout << "pointer holds first: " << ptrUnion.isFirst() << ", points to: " << *ptrUnion.getFirst() << std::endl;
    ptrUnion = &y;
    std::cout << "pointer holds second: " << ptrUnion.isSecond() << ", points to: " << *ptrUnion.getSecond() << std::endl;

    return 0;
}

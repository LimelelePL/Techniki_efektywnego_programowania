#include <iostream>
#include "Union.h"

using namespace std;

int main() {
    Union<int, double> u(5);
    cout << u.isFirst() << std::endl; //1
    cout << u.isSecond() << std::endl; //0
    cout << u.getFirst() << std::endl; //5

    u = 4.0;
    cout << u.isSecond() << std::endl; //1
    cout << u.getSecond() << std::endl; //4

    int a = 10;
    char c = 'x';

    Union<int *, char> up(&a);
    Union<int, char *> uc(&c);

    return 0;
}



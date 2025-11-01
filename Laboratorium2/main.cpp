#include <iostream>

#include "Number.h"
using namespace std;

int main() {
    Number num1(14);
    Number num2(-190);
    Number num3(1);

    Number div1 = num1 / num2;
    cout<<div1.toString()<<endl;

    /*m
     *
    *  num1 = num2;
    *  num1.printNumber();
     *Ten program się wywala, bo w operatorze przypisania przypisałem wskaźnik, a nie dane.
     *Oba obiekty wskazywały na ten sam obszar pamięci,
     *więc po wywołaniu destruktorów wystąpił double delete.
     *Poprawna wersja operatora musi robić głęboką kopię tablicy.”
     */

    /* Po usunięciu destruktora program się nie wywala, ponieważ żaden z obiektów nie próbuje zwolnić pamięci.
     * W ten sposób unikam błędu double delete, ale tracę pamięć zaalokowaną na stercie
     * — występuje wyciek pamięci. Problem nie zniknął, tylko przestał być widoczny
    num1 = num2;
    num1.printNumber();
    */

}

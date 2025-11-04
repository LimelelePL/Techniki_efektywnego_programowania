#include <iostream>

#include "Base256Number.h"
#include "Number.h"
using namespace std;

int main() {
    Number num1(12);
    Number num2(2);
    Number num3(1);

    Number res = num1/num2;
    res.printNumber();

    Base256Number bNum;
    bNum =  17;
    cout<<bNum.toHexString();


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

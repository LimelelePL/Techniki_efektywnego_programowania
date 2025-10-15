#include <iostream>

#include "constans_values.h"
using namespace std;

//zadanie 1 --------------------------------------------------------

void allocTableFill34(int size) {
//stałą VALUE_OF_NUMBER_TO_FILL zadeklarowałem zgodnie z cennikiem bledów w osobnym pliku constans_values.h

    int sizeOfFillArray = size; // nie modyfikujemy parametru

    if (sizeOfFillArray <= 0 || size>=100000) { //warunki dotycznące rozmiaru tablicy
        cout<<"niepoprawny rozmiar tablicy! \n";
        return; //przerywamy funkcję
    }
    int *arr = new int[sizeOfFillArray]; // alokujemy pamięć na stercie

    for (int i = 0; i<sizeOfFillArray; i++) { // inicjalizacja tablicy zmiennych wartoscią 34
        arr[i] = VALUE_OF_NUMBER_TO_FILL;
    }

    for (int i = 0; i<sizeOfFillArray; i++) { //wypisanie tablicy
        cout<<arr[i]<<" ";
    }

    delete [] arr; //zwolnienie nieużywanej juz pamieci
}

//zadanie 2 --------------------------------------------
/* parametr "***table" ponieważ
 *
 */
bool allocTable2Dim(int ***table, int sizeX, int sizeY) {


}

int main() {

    cout<<"ZADANIE 1 \n";
    allocTableFill34(1);
    allocTableFill34(4);
    allocTableFill34(-1);



    return 0;
}
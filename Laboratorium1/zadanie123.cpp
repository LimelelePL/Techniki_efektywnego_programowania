#include <iostream>

#include "constans_values.h"
using namespace std;

//zadanie 1 --------------------------------------------------------

void allocTableFill34(int size) {
//stałą VALUE_OF_NUMBER_TO_FILL zadeklarowałem zgodnie z cennikiem bledów w osobnym pliku constans_values.h
    if (size <= 0 || size>=TOO_LARGE_VALUE) { //warunki dotycznące rozmiaru tablicy
        cout<<"niepoprawny rozmiar tablicy! \n";
        return; //przerywamy funkcję
    }
    int *arr = new int[size]; // alokujemy pamięć na stercie

    for (int i = 0; i<size; i++) { // inicjalizacja tablicy zmiennych wartoscią 34
        arr[i] = VALUE_OF_NUMBER_TO_FILL;
    }

    for (int i = 0; i<size; i++) { //wypisanie tablicy
        cout<<arr[i]<<" ";
    }

    delete [] arr; //zwolnienie nieużywanej juz pamieci
}

//zadanie 2 --------------------------------------------
/*zakladajac ze uzycie referencji jest niemozliwe w parametrze mielibysmy *** */
bool allocTable2Dim(int ***table, int sizeX, int sizeY) {

    if (sizeX<= 0|| sizeY<=0 ||
        sizeX>TOO_LARGE_VALUE || sizeY>TOO_LARGE_VALUE){
        cout<<"niepoprawne rozmiary tablicy \n"; // komunikat o niepoprawnych rozmiarach
        return false;
    }

    // dereferencja bo mamy tylko wskaźnik na adres
    *table = new int*[sizeX]; //alokujemy dynamicznie tablice jednowymiarową wskaznikow na wskaznik
                            //. jej elementy będą wskazywac na "podtablice"

    //inicjalizacja wskaźników tablicy na pierwsze elementy tablic w osi Y
    for (int i = 0; i<sizeX; i++) {
        (*table)[i] = new int[sizeY];
    }

    return true;
}

// zadanie 3

int main() {

    cout<<"ZADANIE 1 \n";
    allocTableFill34(1);
    allocTableFill34(4);
    allocTableFill34(-1);

    cout<<"ZADANIE 2 \n";
    int **tab;
    cout<< allocTable2Dim(&tab, 3, 4) <<"\n";
    cout<< allocTable2Dim(&tab, -1, 4) <<"\n";


    return 0;
}
#include <iostream>

#include "constansValuesFor123.h"
#include "Table.h"
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
//zabezpieczamy rozmiar tablicy i przed podwójną alokacją
    if (table == 0 || *table != 0 || sizeX<= 0|| sizeY<=0 ||
        sizeX>TOO_LARGE_VALUE || sizeY>TOO_LARGE_VALUE){
        cout<<"niepoprawne rozmiary tablicy \n"; // komunikat o niepoprawnych rozmiarach
        return false;
    }

    // dereferencja bo mamy tylko wskaźnik na adres
    *table = new int*[sizeX]; //alokujemy dynamicznie tablice jednowymiarową wskaznikow na wskaznik
                            //. jej elementy będą wskazywac na "podtablice"

    for (int i = 0; i < sizeX; i++) {
        (*table)[i] = new int[sizeY];
    }

  return true;
}

// zadanie 3
//skoro jest zakaz używania referencji
// zadanie 3
// skoro jest zakaz używania referencji
bool deallocTable2Dim(int ***table, int sizeX) {

    // Sprawdzamy czy wskaźnik na tablicę istnieje
    if (table == 0 || *table == 0 ||
        sizeX <= 0 ||
        sizeX > TOO_LARGE_VALUE ) {
        return false;
        }

    // Usuwamy każdą podtablicę (oś Y)
    for (int i = 0; i < sizeX; i++) {
        delete[] (*table)[i];
    }

    // Usuwamy tablicę wskaźników (oś X)
    delete[] *table;

    // Zerujemy wskaźnik (C++98 -> 0)
    *table = 0;

    cout << "usunieto" << endl;
    return true;
}


int main(){
    cout<<"ZADANIE 1 \n";
    allocTableFill34(1);
    allocTableFill34(4);
    allocTableFill34(-1);

    cout<<"ZADANIE 2 \n";
    int **tab1;
    int **tab2;
    cout<< allocTable2Dim(&tab1, 3, 4) <<"\n";
    cout<< allocTable2Dim(&tab2, -1, 4) <<"\n";


    cout<<"ZADANIE 3 \n";
    cout<< deallocTable2Dim(&tab1, 3) <<"\n";
    //cout<< deallocTable2Dim(tab1, -1) <<"\n";

    cout<<"ZADANIE 3 \n";
    //obiekt stworzony przy pomocy konstruktora domyślnego
    Table defaultTable;
    //obiekt stworzony przy pomocy konstruktora z parametrami
    Table parametrizedTable("parametryzowanyTablica", 10);
    // kopiowanie tablicy
    Table copiedTable(parametrizedTable);
    // kopiowanie za pomoca metody clone
    Table *pCloneMethodTable = parametrizedTable.pClone();
    //usuniecie tablicy
    delete pCloneMethodTable;

    Table *pNextClonedMethodTable = parametrizedTable.pClone();


    cout<<"zmieniony size -> metoda setNewSize: " << parametrizedTable.setNewSize(15) <<"\n";
    cout<<"zmieniona nazwa -> metoda setName: " << "\n";
    parametrizedTable.setName("newName");

    defaultTable.modTab(defaultTable, 20);
    pNextClonedMethodTable->modTab(parametrizedTable, 20 );



    return 0;
}
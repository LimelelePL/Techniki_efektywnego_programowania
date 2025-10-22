#include <iostream>

#include "ConstansValuesFor123Tasks.h"
#include "Table.h"
using namespace std;

void displayArray(const int *array, int size) {
    if (array == nullptr || size<=0 || size>= TOO_LARGE_VALUE) {
        cout<<"Błąd przy wypisywaniu tablicy \n";
        return;
    }

    for (int i=0; i<size; i++) {
        cout<< array[i] << " ";
    }
}

void allocTableFill34(int size) {
    if (size <= 0 || size >= TOO_LARGE_VALUE) {
        cout<<"Niepoprawny rozmiar tablicy \n";
        return;
    }

    int* array = new int[size];

    for (int i=0; i<size; i++) {
        array[i] = VALUES_TO_FILL;
    }

    displayArray(array, size);

    cout<<endl;
    delete []array;
}

// *** bo jest to wskaznik na tablice wskaznikow ktora jest ** i musimy uzykać dostęp do jej elementów będącymi
// także wskaźnikami

bool allocTable2Dim(int ***pTable, int sizeX, int sizeY) {
    if (*pTable != nullptr
        || sizeX <= 0 || sizeY<=0 ||
        sizeY>=TOO_LARGE_VALUE || sizeX>=TOO_LARGE_VALUE) {
        cout<<"alokacja nieudana \n";
        return false;
    }

    *pTable = new int*[sizeX];

    for (int i=0; i<sizeX; i++) {
        (*pTable)[i] = new int[sizeY];
    }
    cout<<"alokacja udana \n";
    return true;
}

// z pytania -> tak funkcja deallocTable2Dim nie potrzebuje parametru sizeX, ponieważ możemy usunąć wskaźniki
// na tablice będące kolumnami poruszając się tylko po jednowymiarowej tablicy wskaźników na wskaźniki
bool deallocTable2Dim(int ***pTable, int sizeX) {
    if (pTable == nullptr || *pTable == nullptr ||
        sizeX <= 0 || sizeX >= TOO_LARGE_VALUE) {
        cout << "dealokacja nieudana \n";
        return false;
        }

    // usuwamy każdy wiersz osobno
    for (int i = 0; i < sizeX; i++) {
        delete [] (*pTable)[i];
    }
    // usuwamy tablicę wskaźników
    delete [] *pTable;
    *pTable = nullptr;

    cout << "dealokacja udana \n";
    return true;
}

// procedury do zadania 4

void modTab(Table *pTab, int newSize) {
    if (pTab == nullptr) {
        cout << "Niepoprawny wskaźnik na tablicę!\n";
        return;
    }
    pTab->setNewSize(newSize);

}

void modTab(Table tab, int newSize) {
    tab.setNewSize(newSize);
}


int main() {
    cout<<"=================== ZADANIE 1 ====================== \n";
    allocTableFill34(10);

    cout<<"=================== ZADANIE 2 ====================== \n";
    int** array2 = nullptr;
    allocTable2Dim(&array2, 5, 3);

    cout<<"=================== ZADANIE 3 ====================== \n";
    deallocTable2Dim(&array2, 5);

    cout<<"=================== ZADANIE 4 ====================== \n";
    cout<<"wywolanie konstruktora bezparametry \n\n";
    Table t1;// konstruktor bezparametrowy
    t1.display();
    cout<<"wywolanie konstruktora z parametrym \n\n";
    Table t2("TablicaParam", 5);// konstruktor parametrowy
    t2.display();
    cout<<"wywolanie konstruktora kopiującego \n\n";
    Table t3(t2); // konstruktor kopiujący
    t3.display();

    cout<<"zmiana nazwy \n\n";
    t3.setName("NowaNazwaT3");// zmiana nazwy

    cout<<"zmiana rozmiaru \n\n";
    t2.setNewSize(8); // zmiana rozmiaru tablicy
    t2.display();

    cout<<"klonowanie pClone \n\n";
    Table *t4 = t2.pClone(); // klonowanie

    cout<<"modyfikacja przez wskaznik \n\n";
    modTab(&t2, 3); // modyfikacja przez wskaźnik
    t2.display();

    cout<<"modyfikacja przez wartosc \n\n";
    modTab(t2, 6); // modyfikacja przez wartość (nie zmodyfikuje orginalu)
    t2.display();

    return 0;
}

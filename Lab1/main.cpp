#include <iostream>

#include "constansValuesFor123Tasks.h"
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
    if (*pTable == nullptr || sizeX<=0 || sizeX>=TOO_LARGE_VALUE) {
        cout<<"dealokacja nieudana \n";
        return false;
    }
    for (int i = 0; i<sizeX; i++) {
        delete [] (*pTable)[i];
    }
    delete[] *pTable;
    *pTable = nullptr;

    cout<<"dealokacja udana \n";
    return true;
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
    Table t1;// konstruktor bezparametrowy
    Table t2("TablicaParam", 5);// konstruktor parametrowy
    Table t3(t2); // konstruktor kopiujący

    t3.setName("NowaNazwaT3");// zmiana nazwy
    t2.setNewSize(8); // zmiana rozmiaru tablicy

    Table *t4 = t2.pClone(); // klonowanie
    t2.modTab(&t2, 3); // modyfikacja przez wskaźnik
    t2.modTab(t2, 6); // modyfikacja przez wartość (nie działa)

    delete t4;// usuwamy kopię

    return 0;
}

//
// Created by Dominik on 17.10.2025.
//

#include "Table.h"

#include <iostream>
using namespace std;

Table::Table() {
    name = DEFAULT_NAME;
    length = DEFAULT_LENGTH;
    array = new int[length];
    cout<<"bezp: " + name + "\n";
}
Table::Table(string name, int tableLen) {

    if (tableLen <= 0 || tableLen >=TOO_LARGE_LENGTH) {
        cout<<"niepoprawny rozmiar tablicy, ustawiam rozmiar na domyślny \n";
        length = DEFAULT_LENGTH;
    }else {
        length = tableLen;
    }

    this->name = name;
    array = new int[length];
    cout<<"parametr " + name;
}

Table::Table(const Table &pOther) {

    if (pOther.array == nullptr || pOther.length<=0 || pOther.length>=TOO_LARGE_LENGTH ) {
        cout<<"tablica była niepoprwana! \n";
        length = 0;
        array = nullptr;
        name = "";
    } else {
        name = pOther.name + "Copy";
        length = pOther.length;
        array = new int [length];

        for (int i = 0; i<length; i++) {
            array[i] = pOther.array[i];
        }
    }
    cout << "kopiuj: '" << name << "'" << endl;
}

Table::~Table() {
    if (array != nullptr) {
        delete [] array;
        array = nullptr;
        cout << "usuwam: '" << name << "'" << endl;
    } else {
        cout << "operacja usunięcia na nieistniejącej tablicy!" << endl;
    }
}

void Table::setName(string newName) {
    if (array != nullptr) {
        name = newName;
    } else {
        cout<<"Operacja setName na nieistniejacej tablicy";
    }
}

bool Table::setNewSize(int newTableLen) {
    if (array == nullptr) return false;
    if (newTableLen <= 0 || newTableLen >= TOO_LARGE_LENGTH) return false;

    //tablica pomocnicza do której będziemy kopiować elementy
    int *newArray = new int[newTableLen];
    int elementsToCopy = (newTableLen<length)? newTableLen : length;

    /*
     * w przypadku gdy newTableLen bedzie mniejsze od ówczesniej długości to nie skopiujemy reszty elementów
     */

    for (int i = 0; i < elementsToCopy; i++) {
        newArray[i] = array[i];
    }

    //usuwamy starą tablice
    delete[] array;

    // ustawiamy wskaźnik na tablice o nowej dlugosci
    array = newArray;
    length = newTableLen;

    return true;

}

Table *Table::pClone() {
    if (array == nullptr) {
        cout << "Nie można skopiować tablicy '" << name;
        return nullptr;
    }
    return new Table(*this);
}

void Table::display() {
    if (array == nullptr) return;
    cout << "[";
    for (int i = 0; i<length; i++)
        cout<< array[i] << ", ";
    cout << "]";
    cout<<endl<<endl;
}



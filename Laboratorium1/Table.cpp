//
// Created by Dominik on 16.10.2025.
//
#include "Table.h"

#include <iostream>
using namespace std;

Table::Table() {
    this->name = DEAFAULT_TABLE_NAME;
    cout<<"bezp: " + name + "\n";
    this->arrayLength = DEFAULT_TABLE_LENGTH;
    this->pTable = new int[this->arrayLength];
}
Table::Table(string name, int tableLen) {
    this->name = name;
    this->arrayLength = tableLen;
    cout<<"parametr" + name + "\n";
    this->pTable = new int[this->arrayLength];
}
Table::Table(const Table& pOther) {
    this -> name = pOther.name + "_copy";
    this -> arrayLength = pOther.arrayLength;

    this -> pTable = new int[arrayLength];
    for (int i = 0; i<pOther.arrayLength; i++) {
        this -> pTable[i] = pOther.pTable[i];
    }
    std::cout << "kopiuj: " << this->name << "\n";
}

Table::~Table() {
    if (this->pTable !=nullptr) {
        delete [] this->pTable;
        this->pTable = nullptr;
        cout << "usuwam " << this->name << "\n";
    }
}

void Table::setName(string name) {
    this->name = name;
}

Table *Table::pClone() {
    Table* newTable = new Table(*this);
    return newTable;
}

bool Table::setNewSize(int tabLength) {
    if (tabLength <= this->arrayLength && tabLength>0) {
        if (this->pTable !=nullptr) {
            delete[] this->pTable;
        }
        this->arrayLength = tabLength;
        this->pTable = new int[this->arrayLength];
        return true;
    }
    return false;
}

void Table::modTab(Table *pcTab, int iNewSize) { //modyfikacja bierzącego obiektu
    cout<<"METODA MOD TAB -> wskaźnik \n";
    pcTab->setNewSize(iNewSize);
}
void Table::modTab(Table cTab, int iNewSize) { //zostanie utworzona kopia
    cout<<"METODA MOD TAB -> kopia obiektu \n";
    cTab.setNewSize(iNewSize);
}







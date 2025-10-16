//
// Created by Dominik on 16.10.2025.
//

#ifndef LABORATORIUM1_CTABLE_H
#define LABORATORIUM1_CTABLE_H
#include <string>
using namespace std;

const static string DEAFAULT_TABLE_NAME = "Table_Default";
const static int DEFAULT_TABLE_LENGTH = 2;

class Table {
private:
    string name;
    int arrayLength;
    int *pTable; // wskaznik do dynamicznie alokowanej tablicy int

public:
    Table();
    Table(const Table &pOther);
    Table(string Name, int tableLength);
    ~Table();

    void setName(string name);
    bool setNewSize(int tabLength);
    Table *pClone();
    void modTab(Table *pcTab, int iNewSize);
    void modTab(Table cTab, int iNewSize);
};


#endif //LABORATORIUM1_CTABLE_H
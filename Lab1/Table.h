//
// Created by Dominik on 17.10.2025.
//

#ifndef LAB1_TABLE_H
#define LAB1_TABLE_H
#include <string>
using namespace std;

const int DEFAULT_LENGTH = 1;
const int TOO_LARGE_LENGTH = 10000000;
const string DEFAULT_NAME = "Default array";

class Table {
private:
    int length;
    string name;
    int* array;

public:
    Table();
    Table(string name, int tableLen);

    Table(const Table &pOther);

    ~Table();

    void setName(string newName);
    bool setNewSize(int tableLen);
    Table *pClone();

    void modTab(Table *pTab, int newSize);
    void modTab(Table tab, int newSize);
};


#endif //LAB1_TABLE_H
#include <iostream>
using namespace std;

bool allocate_flat_table(int ***table, int rows, int cols) {
    if (rows <= 0 || cols <= 0) return false;

    int *flat = new int[rows * cols];
    //tablica wskaznikow na wierzse
    *table = new int*[rows];

    //table[0] - poczatek 1 wiersza
    //table[1] - poczatek 2 wiersza

    //ustawiamy wskazniki na poczatek kazdego wiersza - alokacja tablicy
    for (int i = 0; i < rows; i++) {
        (*table)[i] = flat + (i*cols);
    }


    return true;
}

void fill_consecutive_numbers(int **table, int rows, int cols) {
    int v=1;
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            table[i][j] = v++;
        }
    }
}

bool deallocate_flat_table(int ***table) {
    if (table == nullptr) return false;
    delete [](*table)[0]; //bo table[0] = flat
    delete [] *table; //wskazniki na wiersze
    *table = nullptr;
    return true;
}

int main() {
    int **table;

    allocate_flat_table(&table, 2 ,3);
    fill_consecutive_numbers(table, 2, 3);
    std::cout << table[0][1] << " " <<table[1][2] << std::endl;
    deallocate_flat_table(&table);
    return 0;

}
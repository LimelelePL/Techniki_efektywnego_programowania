//
// Created by Dominik on 13.11.2025.
//

#ifndef ZADANIEOB_TREE_H
#define ZADANIEOB_TREE_H


//
// Created by Dominik on 12.11.2025.
//

#ifndef ZADANIE_TREE_H
#define ZADANIE_TREE_H

#include <set>
#include <vector>
#include <string>
using namespace std;

#include "Node.h"
#include "Parser.h"
#include "Error.h"

enum T {
    UNKNOWN, // Zwykle zaczynamy od 0, UNKNOWN jako domyślny
    NUMBER,
    VARIABLE,
    UNARY_OP,
    BINARY_OP,
    ROOT // ROOT zwykle nie jest potrzebny jako typ tokena, ale może być użyty
};

class Tree {
private:
    Node* root;

    Type calculateType(string &value);

    vector<Node*> getUniqueVars(Node* node);
    vector<Node*> getUniqueVars(Node* node, vector<Node*> &result, set<string> &uniqueNodes);

    void print(Node* node);

    Node* buildNode(vector<string> &formula, int &pos, int &addedCount, int &size);

    string doubleToString(double value);
    void replaceAll(Node* node, const string &name, double value);

    Node* getLeaf(Node* node);

    double compute(Node* node);

public:
    Tree();
    Tree(const Tree &copy);
    ~Tree();

    void enter(string formula);
    void vars();
    void comp(vector<double> &values);
    void join(string formula);

    void print();

    Tree& operator=(const Tree &tree);
    Tree operator+(const Tree &tree);
};

#endif //ZADANIE_TREE_H


#endif //ZADANIEOB_TREE_H
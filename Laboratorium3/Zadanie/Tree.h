//
// Created by Dominik on 12.11.2025.
//

#ifndef ZADANIE_TREE_H
#define ZADANIE_TREE_H

#include "Node.h"


class Tree {
private:
    Node* root;

    Type calculateType (const string& value);
    vector<Node*> getVars(Node* node);
    vector<Node*> getVars(Node* node, vector<Node*> nodes);
    void print(Node* node);
    vector<string> split(string formula);
    Node* buildNode (vector<string>& formula, int &pos);
    string doubleToString(double value);

    Node* getLeaf (Node* node);
    double compute (Node* node);

public:
    Tree();
    Tree(const Tree& copy);
    ~Tree();

    void enter(string formula);
    void vars();
    void comp(vector<double>& values);
    void join(string formula);

    void print();

    Tree& operator = (const Tree& tree);
    Tree operator + (const Tree& tree);
};


#endif //ZADANIE_TREE_H
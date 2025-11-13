//
// Created by Dominik on 12.11.2025.
//

#ifndef ZADANIE_TREE_H
#define ZADANIE_TREE_H

#include <set>

#include "Node.h"

#define DEFAULT_NUMBER "1"
#define OP_ADD "+"
#define OP_SUB "-"
#define OP_MUL "*"
#define OP_DIV "/"
#define OP_SIN "sin"
#define OP_COS "cos"


class Tree {
private:
    Node* root;

    Type calculateType (string& value);
    vector<Node*> getUniqueVars(Node* node);
    vector<Node*> getUniqueVars(Node* node, vector<Node*>& result, set<string>& uniqueNodes);
    void print(Node* node);
    vector<string> split(string formula);
    Node* buildNode (vector<string>& formula, int &pos, int& addedCount, int& size);
    string doubleToString(double value);
    void replaceAll(Node* node, const string& name, double value);

    bool isValidNumber(const string& token);
    bool cleanAndValidateVariable(string& token);
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
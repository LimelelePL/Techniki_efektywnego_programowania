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

#include "Parser.h"
#include "Result.h"


class Tree {
public:
    Tree();
    Tree(const Tree& copy);
    ~Tree();

    Result enter(string formula);
    Result vars(vector<string> &outVars);
    Result comp(vector<double>& values, double &outResult);
    Result join(string formula);
    Result print(string &outFormula);

    Tree& operator = (const Tree& tree);
    Tree operator + (const Tree& tree);

private:
    Node* root;

    //Type calculateType (string& value);
    vector<Node*> getUniqueVars(Node* node);
    vector<Node*> getUniqueVars(Node* node, vector<Node*>& result, set<string>& uniqueNodes);
    void print(Node *node, stringstream &ss);

    Node* buildNode(vector<string>& formula, int &pos, int &addedCount, int &size, bool &cleanedLocal);

    string doubleToString(double value);
    void replaceAll(Node* node, const string& name, double value);

    Node* getLeaf (Node* node);
    double compute(Node *node, ErrorCode &err);
    Result makeWarningsResult(vector<string> &warnings, int addedCount, int pos, int size);
};


#endif //ZADANIE_TREE_H
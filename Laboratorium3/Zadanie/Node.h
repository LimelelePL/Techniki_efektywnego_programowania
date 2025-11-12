//
// Created by Dominik on 12.11.2025.
//

#ifndef ZADANIE_NODE_H
#define ZADANIE_NODE_H
#include <string>
#include <vector>
using namespace std;

enum Type {
    NUMBER, VARIABLE, UNARY_OP, BINARY_OP, TENARY_OP, UNKNOWN, ROOT
};

class Node {
private:
    string value;
    Type type;
    Node* parent;
    vector<Node*> children;


public:
    Node();
    Node(string value, Type type);
    ~Node();
    Node(const Node& copy);

    void addChildren(Node* child);
    bool isLeaf() const;

    Node* clone();

    // gettery i settery
    string getValue();
    void setValue(const string &value);

    Type getType();
    void setType(Type type);

    Node * getParent();
    void setParent(Node *parent);

    vector<Node *> &getChildren();
};



#endif //ZADANIE_NODE_H
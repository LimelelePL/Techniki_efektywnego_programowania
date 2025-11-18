//
// Created by Dominik on 13.11.2025.
//

#ifndef ZADANIEOB_NODE_H
#define ZADANIEOB_NODE_H


//
// Created by Dominik on 12.11.2025.
//

#ifndef ZADANIE_NODE_H
#define ZADANIE_NODE_H

#include <string>
#include <vector>
using namespace std;

/*
 * Typ węzła — zgodnie ze specyfikacją z listy 3.
 */
enum Type {
    NUMBER,
    VARIABLE,
    UNARY_OP,
    BINARY_OP,
    TENARY_OP,
    UNKNOWN,
    ROOT
};

class Node {
private:
    string value;            // wartość tekstowa (liczba, zmienna lub operator)
    Type type;               // typ tokena
    Node* parent;            // wskaźnik na rodzica
    vector<Node*> children;  // kopie dzieci węzła

public:
    Node();
    Node(string value, Type type);
    ~Node();
    Node(const Node &copy);

    Node* clone();

    string getValue();
    void setValue(const string &value);

    Type getType();
    void setType(Type type);

    Node* getParent();
    void setParent(Node* parent);

    /*
     * Zwracamy kopię wektora dzieci — pełna enkapsulacja.
     */
    vector<Node*> getChildren();

    void removeChild(Node* child);
    void addChildren(Node* child);

    bool isLeaf() const;
};

#endif //ZADANIE_NODE_H


#endif //ZADANIEOB_NODE_H
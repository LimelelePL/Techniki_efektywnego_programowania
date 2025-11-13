//
// Created by Dominik on 12.11.2025.
//

#include "Node.h"

#include <iostream>

Node::Node() {
    type = UNKNOWN;
    value = "";
    parent = nullptr;
}

Node::Node(string value, Type type) {
    this-> type = type;
    this-> value = value;
    this->parent = nullptr;
}

Node::~Node() {
    for (Node* c : children) {
        if (c!= nullptr) delete c;
    }
    children.clear();
}

Node::Node(const Node &copy) {
    this->value = copy.value;
    this->type = copy.type;
    this->parent = nullptr;

    // kopiujemy reszte dzieci
    for (Node* c : copy.children) {
        Node* newChild = c->clone();
        newChild->setParent(this);
        this->children.push_back(newChild);
    }
}

// kopiujemy całą strukturę od danego node'a w dół
Node * Node::clone() {

    Node* newNode = new Node(value, type);
    newNode->parent = nullptr;

    for (Node* c : children) {
        Node* newChild = c->clone();
        newChild->parent = newNode;
        newNode->children.push_back(newChild);
    }
    return newNode;
}

string Node::getValue() {
    return value;
}

void Node::setValue(const string &value) {
    this->value = value;
}

Type Node::getType() {
    return type;
}

void Node::setType(Type type) {
    this->type = type;
}

Node* Node::getParent() {
    return parent;
}

void Node::setParent(Node* parent) {
    this->parent = parent;
}


vector<Node *> & Node::getChildren() {
    return children;
}


void Node::removeChild(Node* child) {
    vector<Node*>& kids = children;
    for (int i = 0; i < kids.size(); i++) {
        if (kids[i] == child) {
            kids.erase(kids.begin() + i);
            return;
        }
    }
}

void Node::addChildren(Node *child) {
    if (child == nullptr) return;
    child->setParent(this);
    children.push_back(child);

    // if (type == UNARY_OP && children.empty())
    //     children.push_back(child);
    // else if (type == BINARY_OP && children.size() < 2)
    //     children.push_back(child);
    // else if (type == TENARY_OP && children.size() < 3)
    //     children.push_back(child);
    // else if (type == NUMBER || type == VARIABLE || type == UNKNOWN) {
    //     cout << "Uwaga: próba dodania dziecka do liścia '" << value << "'" << endl;
    // }
}

bool Node::isLeaf() const {
    return children.empty();
}

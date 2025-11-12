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
    for (int i = 0; i<children.size(); i++) {
        if (children[i] != nullptr) delete children[i];
    }
    children.clear();
}

Node::Node(const Node &copy) {
    this->value = copy.value;
    this->type = copy.type;
    this->parent = nullptr;

    for (Node* c : children) {
        Node* newChild = c->clone();
        newChild->setParent(this);
        this->children.push_back(newChild);
    }
}

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

void Node::addChildren(Node* child) {
    if (child == nullptr) return;
    child->setParent(this);

    if (type == UNARY_OP && children.size() < 1)
        children.push_back(child);
    else if (type == BINARY_OP && children.size() < 2)
        children.push_back(child);
    else if (type == TENARY_OP && children.size() < 3)
        children.push_back(child);
    else if (type == NUMBER || type == VARIABLE || type == UNKNOWN) {
        cout << "Uwaga: próba dodania dziecka do liścia '" << value << "'" << endl;
    }
}

bool Node::isLeaf() const {
    return children.empty();
}

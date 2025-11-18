//
// Created by Dominik on 12.11.2025.
//

#include "Node.h"

Node::Node() {
    type = UNKNOWN;
    value = "";
    parent = nullptr;
}

Node::Node(string value, Type type) {
    this->value = value;
    this->type = type;
    this->parent = nullptr;
}

Node::~Node() {
    for (Node* c : children) {
        delete c;
    }
    children.clear();
}

Node::Node(const Node &copy) {
    value = copy.value;
    type = copy.type;
    parent = nullptr;

    for (Node* c : copy.children) {
        Node* newChild = c->clone();
        newChild->setParent(this);
        children.push_back(newChild);
    }
}

Node* Node::clone() {
    Node* newNode = new Node(value, type);
    newNode->parent = nullptr;

    for (Node* c : children) {
        Node* copied = c->clone();
        copied->setParent(newNode);
        newNode->children.push_back(copied);
    }
    return newNode;
}

string Node::getValue() { return value; }
void Node::setValue(const string &value) { this->value = value; }

Type Node::getType() { return type; }
void Node::setType(Type type) { this->type = type; }

Node* Node::getParent() { return parent; }
void Node::setParent(Node* parent) { this->parent = parent; }

vector<Node*> Node::getChildren() {
    return children; // kopia — nie ujawniamy wektora prywatnego
}

void Node::removeChild(Node* child) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i] == child) {
            children.erase(children.begin() + i);
            return;
        }
    }
}

void Node::addChildren(Node *child) {
    if (child == nullptr) return;
    child->setParent(this);
    children.push_back(child);
}

bool Node::isLeaf() const {
    return children.empty();
}

#include "Node.h"
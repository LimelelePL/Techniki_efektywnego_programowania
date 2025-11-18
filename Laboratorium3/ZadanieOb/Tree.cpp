//
// Created by Dominik on 12.11.2025.
//

#include "Tree.h"
#include <iostream>
#include <sstream>
#include <cmath>

// ======================= KONSTRUKTORY ==============================

Tree::Tree() {
    root = nullptr;
}

Tree::Tree(const Tree &copy) {
    root = (copy.root ? copy.root->clone() : nullptr);
}

Tree::~Tree() {
    delete root;
}

// ============================= ENTER ==================================

void Tree::enter(string formula) {


    vector<string> tokens = Parser::split(formula);

    int pos = 0;
    int added = 0;
    int size = tokens.size();

    root = buildNode(tokens, pos, added, size);

    if (added > 0) {
        Error::warn("Dodano brakujace elementy formuly. Finalna formula:");
        print();
    }

    if (pos < size) {
        Error::warn("Zignorowano nadmiarowe elementy formuly. Finalna formula:");
        print();
    }
}

// ===================== BUDOWA DRZEWA ================================

Node* Tree::buildNode(vector<string> &formula, int &pos, int &added, int &size) {

    if (pos >= size) {
        added++;
        return new Node(DEFAULT_NUMBER, NUMBER);
    }

    string value = formula[pos++];
    Type type = calculateType(value);

    if (type == UNKNOWN) {
        Error::warn("Nieznany token \"" + value + "\" pominiety.");
        return buildNode(formula, pos, added, size);
    }

    Node *node = new Node(value, type);

    if (type == UNARY_OP) {
        node->addChildren(buildNode(formula, pos, added, size));
    }
    else if (type == BINARY_OP) {
        node->addChildren(buildNode(formula, pos, added, size));
        node->addChildren(buildNode(formula, pos, added, size));
    }

    return node;
}

// ============================ PRINT ================================

void Tree::print() {
    if (root == nullptr) return;
    print(root);
    cout << endl;
}

void Tree::print(Node *node) {
    cout << node->getValue() << " ";
    vector<Node*> kids = node->getChildren();
    for (Node* k : kids)
        print(k);
}

// ========================== VARS =================================

void Tree::vars() {
    vector<Node*> vars = getUniqueVars(root);
    for (Node* v : vars) cout << v->getValue() << " ";
}

vector<Node*> Tree::getUniqueVars(Node* node) {
    vector<Node*> result;
    set<string> unique;
    return getUniqueVars(node, result, unique);
}

vector<Node*> Tree::getUniqueVars(Node* node, vector<Node*> &result, set<string> &unique) {
    if (!node) return result;

    if (node->getType() == VARIABLE) {
        string n = node->getValue();
        if (unique.find(n) == unique.end()) {
            unique.insert(n);
            result.push_back(node);
        }
    }

    vector<Node*> kids = node->getChildren();
    for (Node* k : kids)
        getUniqueVars(k, result, unique);

    return result;
}

// ========================= COMP ==================================

void Tree::comp(vector<double> &values) {
    Tree copy(*this);

    vector<Node*> vars = getUniqueVars(copy.root);

    if (values.size() != vars.size()) {
        Error::warn("Nieprawidlowa liczba wartosci.");
        return;
    }

    for (int i = 0; i < vars.size(); i++) {
        replaceAll(copy.root, vars[i]->getValue(), values[i]);
    }

    cout << "wynik: " << compute(copy.root) << endl;
}

double Tree::compute(Node *node) {
    if (!node) return 0;

    Type t = node->getType();
    string v = node->getValue();

    if (t == NUMBER)
        return atof(v.c_str());

    vector<Node*> kids = node->getChildren();

    if (t == UNARY_OP) {
        double a = compute(kids[0]);
        if (v == OP_SIN) return sin(a);
        if (v == OP_COS) return cos(a);
        return a;
    }

    if (t == BINARY_OP) {
        double l = compute(kids[0]);
        double r = compute(kids[1]);

        if (v == OP_ADD) return l + r;
        if (v == OP_SUB) return l - r;
        if (v == OP_MUL) return l * r;

        if (v == OP_DIV) {
            if (r == 0) {
                Error::warn("Dzielenie przez 0.");
                return 0;
            }
            return l / r;
        }
    }

    return 0;
}

// ============================= JOIN ================================

void Tree::join(string formula) {
    Tree temp;
    temp.enter(formula);
    *this = *this + temp;
}

// ======================== OPERATOR + ==============================

Tree Tree::operator+(const Tree &tree) {
    Tree result(*this);

    if (!tree.root)
        return result;

    Node* other = tree.root->clone();

    if (!result.root) {
        result.root = other;
        return result;
    }

    Node* leaf = result.getLeaf(result.root);
    Node* parent = leaf->getParent();

    if (!parent) {
        delete result.root;
        result.root = other;
        return result;
    }

    parent->removeChild(leaf);
    delete leaf;

    parent->addChildren(other);
    return result;
}

// ======================= OPERATOR = ================================

Tree& Tree::operator=(const Tree &tree) {
    if (this == &tree) return *this;

    delete root;
    root = (tree.root ? tree.root->clone() : nullptr);
    return *this;
}

// ======================= TYPE CHECKING ============================

Type Tree::calculateType(string &value) {

    if (value == OP_SIN || value == OP_COS)
        return UNARY_OP;

    if (value == OP_ADD || value == OP_SUB || value == OP_MUL || value == OP_DIV)
        return BINARY_OP;

    string before = value;

    bool isVar = Parser::cleanVariable(value);
    if (before != value)
        Error::warn("Oczyszczono token: " + value);

    if (isVar)
        return VARIABLE;

    if (Parser::isNumber(value))
        return NUMBER;

    return UNKNOWN;
}

// ======================= PODMIANA ZMIENNYCH =========================

void Tree::replaceAll(Node* node, const string &name, double val) {
    if (!node) return;

    if (node->getType() == VARIABLE && node->getValue() == name) {
        node->setType(NUMBER);
        node->setValue(doubleToString(val));
    }

    vector<Node*> kids = node->getChildren();
    for (Node* k : kids)
        replaceAll(k, name, val);
}

// ======================= SZUKANIE LIŚCIA ===========================

Node* Tree::getLeaf(Node* node) {
    if (!node) return nullptr;
    if (node->isLeaf()) return node;

    vector<Node*> kids = node->getChildren();
    for (Node* k : kids) {
        Node* leaf = getLeaf(k);
        if (leaf) return leaf;
    }
    return nullptr;
}

// ======================= DOUBLE → STRING ===========================

string Tree::doubleToString(double value) {
    stringstream ss;
    ss << value;
    return ss.str();
}


#include "Tree.h"
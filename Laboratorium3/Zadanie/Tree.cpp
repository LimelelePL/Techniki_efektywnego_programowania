//
// Created by Dominik on 12.11.2025.
//

#include "Tree.h"

#include <cmath>
#include <iostream>
#include <sstream>

Tree::Tree() {
    root = nullptr;
}

Tree::Tree(const Tree &copy) {
    root = copy.root->clone();
}

Tree::~Tree() {
    // kolejne węzły usuwane są rekurencyjnie destruktorem klasy Node
    delete root;
}

void Tree::enter(string formula) {
    vector<string> splittedFormula = split(formula);
    int pos = 0;
    delete root;
    root = buildNode(splittedFormula, pos);

    if (pos > splittedFormula.size()) {
        cout << "Uwaga dodano potrzebne czesci formuly, finalna formula: " << endl;
        print();
    }

    if (pos < splittedFormula.size()) {
        cout << "Uwaga zignorowano nadmierne czesci formuly, finalna formula: " << endl;
        print();
    }
}

void Tree::vars() {
    vector<Node *> variables = getVars(root);

    for (Node *v: variables) {
        cout << v->getValue() << " ";
    }
}

/* comp dziala tak, że kopiujemy nasze drzewo do obiektu pomocniczego
 * i zmienne w obiekcie pomocniczym zastępujemy odpowiednimi liczbami
 * następnie obliczamy wartość wyrażenia dla samych liczb w funkcji
 * pomocniczej compute(*Node)
 */
void Tree::comp(vector<double> &values) {
    Tree copy(*this);

    vector<Node *> variables = getVars(copy.root);

    if (values.size() != variables.size()) {
        cout << "Ilość wartości nie zgadza się z ilością zmiennych!" << endl;
        return;
    }

    // w kopii drzewa kazda zmienna zamieniamy na liczbe
    for (int i = 0; i < variables.size(); i++) {
        variables[i]->setType(NUMBER);
        variables[i]->setValue(doubleToString(values[i]));
    }

    cout << "wynik: " << compute(copy.root) << endl;
}

void Tree::print() {
    print(root);
}

// wypisywanie typu preorder
void Tree::print(Node *node) {
    if (node == nullptr) {
        return;
    }
    cout << node->getValue() << " ";
    for (Node *child: node->getChildren()) {
        print(child);
    }
}

void Tree::join(string formula) {
}

void Tree::operator=(const Tree &tree) {
    root = tree.root->clone();
}

Tree Tree::operator+(const Tree &tree) {

}

// rekurencyjnie budujemy nasze drzewo
Node *Tree::buildNode(vector<string> &formula, int &pos) {
    // warunek ten oznacza, że brakuje nam elementów przy danym operatorze
    // należy wiec je uzupelnic
    if (pos >= formula.size()) {
        cout << "zastepuje braki jedynkami \n";
        return new Node("1", NUMBER);
    }

    string value = formula[pos++];

    Type type = calculateType(value);

    Node *node = new Node(value, type);

    // jednorguentowy -> jedno dziecko
    if (type == UNARY_OP) {
        node->addChildren(buildNode(formula, pos));
    }
    //dwuargumentowy -> dwoje dzieci
    else if (type == BINARY_OP) {
        node->addChildren(buildNode(formula, pos));
        node->addChildren(buildNode(formula, pos));
    }
    // w przeciwym gdy liczba lub zmienna to cofamy się w rekurencji
    // aby uzupełnić braki dla reszty operatorów
    return node;
}

//metoda dzieląca formułę na operatory według spacji
vector<string> Tree::split(string formula) {
    vector<string> result;
    string word;

    for (int i = 0; i < formula.length(); i++) {
        if (formula[i] != ' ')
            word += formula[i];
        else if (!word.empty()) {
            result.push_back(word);
            word = "";
        }
    }

    if (!word.empty()) result.push_back(word);
    return result;
}

// metoda sprawdzająca typ danego operatora
Type Tree::calculateType(const string &value) {
    if (value.empty()) return UNKNOWN;
    if (value == "sin" || value == "cos") return UNARY_OP;
    if (value == "+" || value == "-" || value == "*" || value == "/") return BINARY_OP;
    if (isdigit(value[0])) return NUMBER;
    if (isalpha(value[0])) return VARIABLE;
    return UNKNOWN;
}


vector<Node *> Tree::getVars(Node *node) {
    vector<Node *> temp;
    return getVars(node, temp);
}

//taka implemenacja bo podniej vector vars ktory stąd wezmiemt przyda nam sie do comp;
vector<Node *> Tree::getVars(Node *node, vector<Node *> nodes) {
    vector<Node *> result = nodes;
    if (node == nullptr) {
        return result;
    }

    if (node->getType() == VARIABLE) {
        //cout<<"dodaje " << node->getValue() << endl;
        result.push_back(node);
    }

    for (Node *child: node->getChildren()) {
        result = getVars(child, result);
    }

    return result;
}


double Tree::compute(Node *node) {
    if (node == nullptr) return 0;

    string value = node->getValue();
    Type type = node->getType();

    // jezeli liczba to zwracamy wynik (liczbe) do operator
    if (type == NUMBER) {
        return atof(value.c_str());
    }

    //raczej nie powinno sie wydarzyć
    if (type == VARIABLE) {
        return 0;
    }

  // w obu operatorach musimy zejsc tak nisko w rekrencji aż otrzymają
    // jednoargumentowy jedną liczbę
    // dwuargumentowy dwie liczby
    if (type == UNARY_OP) {
        vector<Node *> &kids = node->getChildren();
        if (kids.empty()) return 0;
        double arg = compute(kids[0]);
        if (value == "sin") return sin(arg);
        if (value == "cos") return cos(arg);
        return arg;
    }

    if (type == BINARY_OP) {
        vector<Node *> &kids = node->getChildren();
        if (kids.size() < 2) return 0; // brakujące argumenty

        double left = compute(kids[0]);
        double right = compute(kids[1]);

        if (value == "+") return left + right;
        if (value == "-") return left - right;
        if (value == "*") return left * right;
        if (value == "/") {
            if (right == 0) {
                cout << "Dzielenie przez 0!" << endl;
                return 0;
            }
            return left / right;
        }
    }

    return 0;
}


string Tree::doubleToString(double value) {
    stringstream ss;
    ss << value;
    return ss.str();
}


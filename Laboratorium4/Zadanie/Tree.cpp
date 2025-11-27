//
// Created by Dominik on 12.11.2025.
//

#include "Tree.h"

#include <cmath>
#include <sstream>

#include "Parser.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

Tree::Tree() {
    root = nullptr;
}

Tree::Tree(const Tree &copy) {
    root = (copy.root ? copy.root->clone() : nullptr);
}

Tree::~Tree() {
    // kolejne węzły usuwane są rekurencyjnie destruktorem klasy Node
    delete root;
}

// ==========================================ENTER =============================================
Result Tree::enter(string formula) {
    bool cleanedLocal = false;
    vector<string> splittedFormula = Parser::split(formula);

    int pos = 0;
    int addedCount = 0;
    int size = static_cast<int>(splittedFormula.size());

    delete root; // usuwamy stare drzewo
    root = nullptr;

    root = buildNode(splittedFormula, pos, addedCount, size, cleanedLocal);

    vector<string> warnings;
    if (cleanedLocal) {
        warnings.push_back("Zignorowano niedozwolone znaki w tokenach.");
    }

    if (root == nullptr) {
        return Result::success();
    }

    if (addedCount > 0) {
        warnings.push_back("Dodano brakujace częsci formuly.");
    }

    if (pos < size) {
        warnings.push_back("Zignorowano nadmierne czesci formuly.");
    }

    if (!warnings.empty()) return makeWarningsResult(warnings, addedCount, pos, size);

    return Result::success();
}


// metoda ktora rekurencyjnie buduje nasze drzewo
Node* Tree::buildNode(vector<string> &formula, int &pos, int &addedCount, int &size, bool &cleanedLocal) {

    // warunek ten oznacza, że brakuje nam elementów przy danym operatorze
    // należy wiec je uzupelnic
    if (pos >= size) {
        addedCount++;
        return new Node(DEFAULT_NUMBER, NUMBER);
    }

    string value = formula[pos++];

    string before = value;
    Type type = Parser::calculateType(value);
    string after = value;

    if (before != after) {
        cleanedLocal = true;
    }

    if (type == UNKNOWN) {
        //pomijamy błędną zmienną
        return buildNode(formula, pos, addedCount, size, cleanedLocal);
    }

    Node *node = new Node(value, type);

    // jednorguentowy -> jedno dziecko
    if (type == UNARY_OP) {
        node->addChildren(buildNode(formula, pos, addedCount,size, cleanedLocal));
    }
    //dwuargumentowy -> dwoje dzieci
    else if (type == BINARY_OP) {
        // najpiew lewe dziecko
        node->addChildren(buildNode(formula, pos,addedCount,size, cleanedLocal));
        // potem prawe
        node->addChildren(buildNode(formula, pos,addedCount,size, cleanedLocal));
    }
    // w przeciwym gdy liczba lub zmienna to cofamy się w rekurencji
    // aby uzupełnić braki dla reszty operatorów
    return node;
}

//===========================================================================================

//====================================COMP=========================================
/* comp dziala tak, że kopiujemy nasze drzewo do obiektu pomocniczego
 * i zmienne w obiekcie pomocniczym zastępujemy odpowiednimi liczbami
 * następnie obliczamy wartość wyrażenia dla samych liczb w funkcji
 * pomocniczej compute(*Node)
 */
Result Tree::comp(vector<double> &values, double &outResult) {
    outResult = 0.0;

    if (root == nullptr) {
        return Result(ERR_EMPTY_TREE, "Drzewo jest puste." );
    }

    Tree copy(*this);
    vector<Node *> variables = getUniqueVars(copy.root);

    if (values.size() != variables.size()) {
        return Result(ERR_COMP_VALUE_MISMATCH, "Ilosc wartosci nie zgadza się z iloscia zmiennych." );
    }
    if (values.size() == 0) {
        return Result(ERR_COMP_VALUE_MISMATCH, "Brak arumentów w funkcji compen" );
    }

    // w kopii drzewa kazda zmienna zamieniamy na liczbe
    for (int i = 0; i < variables.size(); i++) {
        string varName = variables[i]->getValue();
        replaceAll(copy.root, varName, values[i]);
    }

    ErrorCode err = OK;
    double result = compute(copy.root, err);

    if (err != OK) {
        if (err == ERR_DIV_BY_ZERO) {
            return Result(ERR_DIV_BY_ZERO, "Dzielenie przez 0.");
        }
        return Result(err, "Blad obliczen.");
    }

    outResult = result;
    return Result::success();
}


double Tree::compute(Node *node, ErrorCode &err) {
    if (node == nullptr || err != OK) return 0;

    string value = node->getValue();
    Type type = node->getType();

    // jezeli liczba to zwracamy wynik (liczbe) do operator
    if (type == NUMBER) {
        return atof(value.c_str());
    }

    //raczej nie powinno sie wydarzyć po zmieanie zmiennych na liczby
    if (type == VARIABLE) {
        return 0;
    }

    // w obu operatorach musimy zejsc tak nisko w rekrencji aż otrzymają
    // jednoargumentowy jedną liczbę
    // dwuargumentowy dwie liczby
    if (type == UNARY_OP) {
        vector<Node *> kids = node->getChildren();
        if (kids.empty()) return 0;
        double arg = compute(kids[0], err);
        if (value == OP_SIN) return sin(arg);
        if (value == OP_COS) return cos(arg);
        return arg;
    }

    if (type == BINARY_OP) {
        vector<Node *> kids = node->getChildren();
        if (kids.size() < 2) return 0; // brakujące argumenty

        double left = compute(kids[0],err);
        double right = compute(kids[1],err);

        if (value == OP_ADD) return left + right;
        if (value == OP_SUB) return left - right;
        if (value == OP_MUL) return left * right;
        if (value == OP_DIV) {
            if (right == 0) {
                err = ERR_DIV_BY_ZERO;
                return 0;
            }
            return left / right;
        }
    }

    return 0;
}

//=================================================================================================

// ========================== VARS ==================================
Result Tree::vars(vector<string> &outVars) {
    outVars.clear();

    if (root == nullptr) {
        return Result(ERR_EMPTY_TREE, "Drzewo jest puste.");
    }

    vector<Node *> variables = getUniqueVars(root);

    for (Node *v: variables) {
        outVars.push_back(v->getValue());
    }
    return Result::success();
}

// metoda zwracająca unikalne zmienne z drzewa
vector<Node *> Tree::getUniqueVars(Node *node) {
    vector<Node *> temp;
    set<string> uniqueNodes;
    return getUniqueVars(node, temp,uniqueNodes);
}

//metoda zwracająca unikalne zmienne z drzewa
vector<Node *> Tree::getUniqueVars(Node *node, vector<Node *> &result, set<string> &uniqueNodes) {
    if (node == nullptr) {
        return result;
    }

    if (node->getType() == VARIABLE) {
        string varName = node->getValue();
        // jezeli jest taka sama zmienna to jej nie powtarzamy w wynikowej liscie
        if (uniqueNodes.find(varName) == uniqueNodes.end()) {
            result.push_back(node);
            uniqueNodes.insert(varName);
        }
    }

    //wywołujemy metode rekurencyjnie dla poddrzew
    for (Node *child: node->getChildren()) {
        result = getUniqueVars(child, result, uniqueNodes);
    }

    return result;
}

// ==================================PRINT ==============================================
Result Tree::print(string &outFormula) {
    outFormula = "";

    if (root == nullptr) {
        return Result(ERR_EMPTY_TREE, "Drzewo jest puste.");
    }

    stringstream ss;
    print(root, ss);
    outFormula = ss.str();

    return Result::success();
}
// wypisywanie typu preorder
void Tree::print(Node *node, stringstream &ss) {
    if (node == nullptr) {
        return;
    }

    ss << node->getValue() << " ";

    vector<Node*> children = node->getChildren();
    for (Node* c : children) {
        print(c, ss);
    }
}

//===============================================================================================

// =============================JOIN=====================================

Result Tree::join(string formula) {
    Tree tree;
    Result r = tree.enter(formula);
    if (r.getCode() != OK) {
        return r;
    }

    *this = *this + tree;
    return Result::success();
}
//=============================================================

// =========================== OPERATOR + ==========================
Tree Tree::operator+(const Tree &tree) {
    Tree result(*this);

    if (tree.root == nullptr) {
        return result;
    }

    Node *otherRoot = tree.root->clone();

    // jak nasze drzewo jest puste, to wynikiem jest po prostu kopia tree
    if (result.root == nullptr) {
        result.root = otherRoot;
        return result;
    }

    // zamiast danego liscia przypinamy korzen drugiego drzewa
    Node* leaf = result.getLeaf(result.root);
    Node* parent = leaf->getParent();

    if (parent == nullptr) {
        delete result.root;
        result.root = otherRoot;
        return result;
    }

    parent->removeChild(leaf);
    delete leaf;

    parent->addChildren(otherRoot);

    return result;
}

// ============================= OPERATOR = ==========================================
Tree& Tree::operator=(const Tree &tree) {
    if (this == &tree) return *this;

    delete root;
    root = tree.root->clone();

    return *this;
}

// ============================================================================



// metoda zmieniająca każdą zmienną w drzewie o nazwie "name" na liczbe "value"
void Tree::replaceAll(Node* node, const string& name, double value){
    if (!node) return;

    if (node->getType() == VARIABLE && node->getValue() == name) {
        node->setType(NUMBER);
        node->setValue(doubleToString(value));
    }

    for (Node* child : node->getChildren()) {
        replaceAll(child, name, value);
    }
}

//metoda zwracająca dowolny liść
Node* Tree::getLeaf(Node* node) {
    if (node == nullptr) return nullptr;
    if (node->isLeaf()) return node;

    vector<Node*> kids = node->getChildren();
    for (Node* k : kids) {
        Node* leaf = getLeaf(k);
        if (leaf != nullptr) return leaf;
    }
    return nullptr;
}

string Tree::doubleToString(double value) {
    stringstream ss;
    ss << value;
    return ss.str();
}


Result Tree::makeWarningsResult(vector<string> &warnings, int addedCount, int pos, int size) {
    // doda osjmytateczna formułe
    string finalFormula;
    Result pr = this->print(finalFormula);
    if (pr.getCode() == OK && !finalFormula.empty()) {
        warnings.push_back(string("Ostateczna formula: ") + finalFormula);
    }

    // wybieramy kod
    ErrorCode code = WARN_CLEANED_TOKEN;
    if (addedCount > 0) code = WARN_MISSING_TOKENS;
    else if (pos < size) code = WARN_EXTRA_TOKENS;

    // łączymy komunikaty w jedną wiadomość wieloliniową
    string msg;
    for (size_t i = 0; i < warnings.size(); ++i) {
        msg += warnings[i];
        if (i + 1 < warnings.size()) msg += "\n";
    }
    return Result(code, msg);
}

int Tree::calcWidth(Node* n, map<Node*, int>& width) {
    vector<Node*> ch = n->getChildren();

    // liść
    if (ch.empty()) {
        width[n] = 1;
        return 1;
    }

    // jeden potomek to szerokość taka jak dziecko
    if (ch.size() == 1) {
        int wChild = calcWidth(ch[0], width);
        width[n] = wChild;
        return wChild;
    }

    // wiele dzieci to szerokość to suma szerokości dzieci
    int sum = 0;
    for (int i = 0; i < (int)ch.size(); i++) {
        sum += calcWidth(ch[i], width);
    }

    width[n] = sum;
    return sum;
}


void Tree::assignColsDFS(Node* n, map<Node*, int>& col, int &nextX) {
    vector<Node*> children = n->getChildren();

    // jeśli liść nadajemy kolejną pozycję
    if (children.empty()) {
        col[n] = nextX;
        nextX += 2;
        return;
    }

    // najpierw pozcjnojmey dzeci
    for (int i = 0; i < static_cast<int>(children.size()); i++) {
        assignColsDFS(children[i], col, nextX);
    }

    // potem rodzic
    if (children.size() == 1) {
        // ejdno dziecko to rodzic nad nim
        col[n] = col[children[0]];
    } else {
        // jak wiecej dzieic to stoi pomiedzy dziecmi i nad nimi
        int first = col[children[0]];
        int last  = col[children[children.size() - 1]];
        col[n] = (first + last) / 2;
    }
}


Result Tree::draw() {
    if (root == nullptr) {
        return Result(ERR_EMPTY_TREE, "Drzewo jest puste.");
    }

    // zbieramy wezly bfs
    vector<vector<Node*> > levels;
    vector<Node*> current;
    current.push_back(root);

    while (!current.empty()) {
        levels.push_back(current);
        vector<Node*> next;

        for (int i = 0; i < static_cast<int>(current.size()); i++) {
            vector<Node*> ch = current[i]->getChildren();
            for (int j = 0; j < static_cast<int>(ch.size()); j++) {
                next.push_back(ch[j]);
            }
        }

        current = next;
    }

    int h = (int)levels.size();

    // kolmuny dfsem po liscuach
    map<Node*, int> col;
    int nextX = 1;
    assignColsDFS(root, col, nextX);

    // maksynalna kolumna
    int maxCol = 0;
    for (map<Node*, int>::iterator it = col.begin(); it != col.end(); ++it) {
        if (it->second > maxCol) maxCol = it->second;
    }

    const int SCALE = 1;
    int totalWidth = maxCol * SCALE + 1;

    vector<string> output(h, string(totalWidth, ' '));

    // Wstawiamy gwiazdki
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < static_cast<int>(levels[i].size()); j++) {
            Node* n = levels[i][j];
            int c = col[n] * SCALE;

            if (c >= 0 && c < totalWidth) {
                output[i][c] = '*';
            }
        }
    }

    for (int i = 0; i < h; i++) {
        cout << output[i] << endl;
    }

    return Result::success();
}











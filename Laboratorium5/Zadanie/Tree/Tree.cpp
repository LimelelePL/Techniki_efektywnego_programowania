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

#include "Error.h"

using namespace std;

int Tree::copyCtorCount = 0;
int Tree::copyAssignCount = 0;
int Tree::moveCtorCount = 0;
int Tree::moveAssignCount = 0;

Tree::Tree() {
    root = nullptr;
}

Tree::~Tree() {
    // kolejne węzły usuwane są rekurencyjnie destruktorem klasy Node
    delete root;
}

Tree::Tree(const Tree &copy) {
    copyCtorCount++;
    root = copy.root ? copy.root->clone() : nullptr;
}

Tree::Tree(Tree &&other) {
    moveCtorCount++;
    root = other.root;
    other.root = nullptr;
}

Tree& Tree::operator=(Tree &&other) noexcept {
    ++moveAssignCount;
    if (this == &other) return *this;

    delete root;
    root = other.root;
    other.root = nullptr;

    return *this;
}

Tree Tree::operator=(const Tree &tree) {
    copyAssignCount++;
    if (this == &tree) return *this;

    delete root;
    root = tree.root->clone();

    return *this;
}

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

void Tree::resetCounters() {
    copyCtorCount = copyAssignCount = moveCtorCount = moveAssignCount = 0;
}

void Tree::printCounters() {
    cout<<"konstruktor move: " << moveCtorCount  << endl;
    cout<<"konstruktor copy: " << copyCtorCount << endl;
    cout<<"operator przypisania z move : " << moveAssignCount  << endl;
    cout<<"operator przypisania : " << copyAssignCount << endl;

}


// ==========================================ENTER =============================================
Result<void, Error> Tree::enter(const std::string &formula){
    bool cleanedLocal = false;

    std::vector<std::string> splittedFormula = Parser::split(formula);
    int pos = 0;
    int addedCount = 0;
    int size = (int) splittedFormula.size();

    // usuwamy poprzednie drzewo

    delete root;
    root = nullptr;

    // budujemy nowe drzewo
    root = buildNode(splittedFormula, pos, addedCount, size, cleanedLocal);

    std::vector<std::string> warnings;

    //pusta formuła albo wszystko zignorowane
    if (root == nullptr) {
        return Result<void, Error>::ok();
    }

    if (cleanedLocal) {
        warnings.push_back("Zignorowano niedozwolone znaki w tokenach.");
    }

    if (addedCount > 0) {
        warnings.push_back("Dodano brakujace czesci formuly: finalna formula: " + print().getValue());
    }

    if (pos < size) {
        warnings.push_back("Zignorowano nadmierne części formuly finalna formula: " + print().getValue());
    }

    if (warnings.empty()) {
        return Result<void, Error>::ok();
    }

    // w przeciwnym razie tworzymy listę bledow
    std::vector<Error*> errList;

    for (string &w : warnings) {
        errList.push_back(new Error(w));
    }

    Result<void, Error> res = Result<void, Error>::fail(errList);
    // Result przejmuje własność przekazanych Error* i czyści errList dlatego nie suuwamy ich pozniej

    return res;
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
Result<double, Error> Tree::comp(std::vector<double> &values)
{
    if (root == nullptr)
        return Result<double, Error>::fail(new Error("Drzewo jest puste."));

    Tree copy(*this);
    vector<Node*> vars = getUniqueVars(copy.root);

    if (vars.size() != values.size())
        return Result<double, Error>::fail(new Error("Liczba wartosci nie zgadza sie z liczba zmiennych."));

    // podmieniamy wartości zmiennych
    for (int i = 0; i < vars.size(); i++)
        replaceAll(copy.root, vars[i]->getValue(), values[i]);

    // liczymy
    return compute(copy.root);
}


Result<double, Error> Tree::compute(Node* node)
{
    if (node == nullptr)
        return Result<double, Error>::fail(new Error("Niepoprawne drzewo."));

    std::string value = node->getValue();
    Type type = node->getType();

    // ========================= LICZBA =========================
    if (type == NUMBER) {
        double v = atof(value.c_str());
        return Result<double, Error>::ok(v);
    }

    // ========================= ZMIENNA =========================
    if (type == VARIABLE) {
        return Result<double, Error>::fail(
            new Error("Nie wszystkie zmienne zostaly podstawione.")
        );
    }

    // ========================= UNARNY =========================
    if (type == UNARY_OP) {
        Result<double, Error> childRes = compute(node->getChildren()[0]);
        if (!childRes.isSuccess()) return childRes;

        double arg = childRes.getValue();

        if (value == OP_SIN) return Result<double, Error>::ok(sin(arg));
        if (value == OP_COS) return Result<double, Error>::ok(cos(arg));

        return Result<double, Error>::ok(arg);
    }

    // ========================= BINARNY =========================
    if (type == BINARY_OP) {
        Result<double, Error> leftRes  = compute(node->getChildren()[0]);
        if (!leftRes.isSuccess()) return leftRes;

        Result<double, Error> rightRes = compute(node->getChildren()[1]);
        if (!rightRes.isSuccess()) return rightRes;

        double L = leftRes.getValue();
        double R = rightRes.getValue();

        if (value == OP_ADD) return Result<double, Error>::ok(L + R);
        if (value == OP_SUB) return Result<double, Error>::ok(L - R);
        if (value == OP_MUL) return Result<double, Error>::ok(L * R);
        if (value == OP_DIV) {
            if (R == 0)
                return Result<double, Error>::fail(new Error("Dzielenie przez zero."));
            return Result<double, Error>::ok(L / R);
        }
    }

    return Result<double, Error>::fail(new Error("Nieznany operator."));
}


//=================================================================================================

// ========================== VARS ==================================
Result<string, Error> Tree::vars()
{
    if (root == nullptr)
        return Result<string, Error>::fail(new Error("Drzewo jest puste."));

    vector<Node*> varNodes = getUniqueVars(root);
    string out;

    for (Node* n : varNodes)
        out += n->getValue();

    return Result<string, Error>::ok(out);
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
Result<string, Error> Tree::print()
{
    if (root == nullptr)
        return Result<string, Error>::fail(new Error("Drzewo jest puste."));

    stringstream ss;
    print(root, ss);
    return Result<string, Error>::ok(ss.str());
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

Result<void, Error> Tree::join(const std::string &formula)
{
    Tree other;
    Result<void, Error> r = other.enter(formula);

    *this = *this + other;
    return r;
}

//=============================================================

// =========================== OPERATOR + ==========================


// ============================= OPERATOR = ==========================================

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

Result<Tree*, Error> Tree::exportTree()
{
    if (root == nullptr)
        return Result<Tree*, Error>::fail(new Error("Drzewo jest puste."));


    return Result<Tree*, Error>::ok(new Tree(*this));
}


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
    root = (copy.root ? copy.root->clone() : nullptr);
}

Tree::~Tree() {
    // kolejne węzły usuwane są rekurencyjnie destruktorem klasy Node
    delete root;
}

// ==========================================ENTER =============================================
void Tree::enter(string formula) {
    if (root!=nullptr) {
        cout<<"proba dodania do drzewa zawierajacego juz formule ";
        return;
    }

    vector<string> splittedFormula = split(formula);

    int pos = 0;
    int addedCount = 0;
    int size = splittedFormula.size();
    delete root;
    root = buildNode(splittedFormula, pos, addedCount, size);

    if (addedCount> 0) {
        cout << "UWAGA! dodano potrzebne czesci formuly, finalna formula: " << endl;
        print();
    }

    if (pos < size) {
        cout << "UWAGA! zignorowano nadmierne czesci formuly, finalna formula: " << endl;
        print();
    }
}


// metoda ktora rekurencyjnie buduje nasze drzewo
Node *Tree::buildNode(vector<string> &formula, int &pos, int &addedcount, int& size) {

    // warunek ten oznacza, że brakuje nam elementów przy danym operatorze
    // należy wiec je uzupelnic
    if (pos >= size) {
        addedcount++;
        return new Node("1", NUMBER);
    }

    string value = formula[pos++];
    Type type = calculateType(value);

    if (type == UNKNOWN) {
        cout << "UWAGA: Napotkano nieznany symbol \"" << value
        << "\". Pomijanie i kontynuacja parsowania." << endl;

        //pomijamy błędną zmienną
        return buildNode(formula, pos, addedcount, size);
    }

    Node *node = new Node(value, type);

    // jednorguentowy -> jedno dziecko
    if (type == UNARY_OP) {
        node->addChildren(buildNode(formula, pos, addedcount,size));
    }
    //dwuargumentowy -> dwoje dzieci
    else if (type == BINARY_OP) {
        // najpiew lewe dziecko
        node->addChildren(buildNode(formula, pos,addedcount,size));
        // potem prawe
        node->addChildren(buildNode(formula, pos,addedcount,size));
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

//===========================================================================================

//====================================COMP=========================================
/* comp dziala tak, że kopiujemy nasze drzewo do obiektu pomocniczego
 * i zmienne w obiekcie pomocniczym zastępujemy odpowiednimi liczbami
 * następnie obliczamy wartość wyrażenia dla samych liczb w funkcji
 * pomocniczej compute(*Node)
 */
void Tree::comp(vector<double> &values) {
    Tree copy(*this);

    vector<Node *> variables = getUniqueVars(copy.root);


    if (values.size() != variables.size()) {
        cout << "Ilosc wartosci nie zgadza się z iloscia zmiennych!" << endl;
        return;
    }

    // w kopii drzewa kazda zmienna zamieniamy na liczbe
    for (int i = 0; i < variables.size(); i++) {
        string varName = variables[i]->getValue();
        replaceAll(copy.root, varName, values[i]);
    }


    cout << "wynik: " << compute(copy.root) << endl;
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

//=================================================================================================

// ========================== VARS ==================================
void Tree::vars() {
    vector<Node *> variables = getUniqueVars(root);

    for (Node *v: variables) {
        cout << v->getValue() << " ";
    }
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
void Tree::print() {
    if (root == nullptr) return;
    print(root);
    cout<<endl;
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

//===============================================================================================

// =============================JOIN=====================================

void Tree::join(string formula) {
    Tree tree;
    tree.enter(formula);
    *this = *this + tree;
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

// metoda sprawdzająca typ operacji z danego stringa
Type Tree::calculateType(std::string &value) {
    if (value.empty()) return UNKNOWN;

    if (value == "sin" || value == "cos") return UNARY_OP;
    if (value == "+" || value == "-" || value == "*" || value == "/") return BINARY_OP;

    /* żeby znazwa zmiennej była poprawna to:
     * - musi zawierac co najmniej jedną wielką lub małą literę
     * - nie może zawierać znaków specjalnych
     * - może zawierać liczbę, jeżeli zawiera co najmniej jedną litere
     */

    // nazwa zmiennej przed naprawą
    string before = value;

    bool containsLetter = cleanAndValidateVariable(value);

    // nazwa zmiennej po naprawie
    string after = value;

    // usunięto niedozwolone znaki
    if (before != after) {
        cout << "UWAGA: Niedozwolone znaki zostaly zignorowane. Token po oczyszczeniu: \""
             << after << "\"" << endl;
    }

    // jesli wynik ma litere to jest zmienna
    if (containsLetter) {
        return VARIABLE;
    }

    // jeśli po oczyszczeniu wartosc wygląda jak liczba zmieniamy na liczbe i dajemy komuniakt
    if (isValidNumber(value)) {
        if (before != after) {
            cout << "UWAGA: Token \"" << before
                 << "\" po oczyszczeniu jest liczba: " << after << endl;
        }
        return NUMBER;
    }

    return UNKNOWN;
}

// metoda sprawdzająca czy napis jest liczbą całkowitą dodatnią
bool Tree::isValidNumber(const string &token) {
    if (token.empty()) return false;

    for (char c : token) {
        if (!isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

// metoda naprawiająca zmienną
bool Tree::cleanAndValidateVariable(string &token) {
    string original = token;
    string cleanToken;

    bool containsLetter = false;

    for (int i = 0; i < token.length(); ++i) {
        char c = token[i];

        // litery i cyfry są dozwolone
        if (isalnum((unsigned char)c)) {
            cleanToken += c;
            if (isalpha(c)) containsLetter = true;
        }
    }

    token = cleanToken;

    // jezeli nie ma litery jest niepoprawna
    if (!containsLetter) return false;

    // Nazwa zmiennej nie może być pusta
    return !token.empty();
}


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

    vector<Node*>& kids = node->getChildren();
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


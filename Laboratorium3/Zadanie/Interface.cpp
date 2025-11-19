
#include "Interface.h"

#include <iostream>
#include <sstream>
using namespace std;

void Interface::printError(const Result &r) {

    if (r.getCode() == OK) return;

    switch (r.getCode()) {
        case ERR_EMPTY_TREE:
            cout << "BLAD: drzewo jest puste." << endl;
            break;
        case ERR_COMP_VALUE_MISMATCH:
            cout << "BLAD: liczba wartosci nie zgadza sie z liczba zmiennych." << endl;
            break;
        case ERR_DIV_BY_ZERO:
            cout << "BLAD: dzielenie przez zero." << endl;
            break;
        default:
            if (!r.getMessage().empty()) {
                // rozbiyjamy  komunikat na osobne linie i wypisujemy każdy
                string line;
                stringstream ss(r.getMessage());
                while (getline(ss, line, '\n')) {
                    if (!line.empty()) cout << "UWAGA: " << line << endl;
                }
            }
            break;
    }
}

void Interface::run() {
    string line;

    cout << "=== INTERFEJS DRZEWA FORMUL ===" << endl;
    cout << "Dostepne polecenia:" << endl;
    cout << " enter <formula>" << endl;
    cout << " print" << endl;
    cout << " vars" << endl;
    cout << " comp <v1> <v2> ..." << endl;
    cout << " join <formula>" << endl;
    cout << " exit" << endl;
    cout << "===============================" << endl;

    while (true) {
        cout << ">";
        if (!getline(cin, line)) return;

        // pobieramy pierwsze słowo jako komendę, resztę jako argumenty
        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd.empty()) continue;

        if (cmd == "exit") {
            return;
        }

        if (cmd == "enter") {
            string f;
            getline(iss, f); // pobiera resztę linii (może być pusta lub zaczynać spacją)
            if (!f.empty() && f[0] == ' ') f.erase(0, 1);
            Result r = tree.enter(f);
            printError(r);
        }
        else if (cmd == "print") {
            string formula;
            Result r = tree.print(formula);
            if (r.getCode() == OK) {
                cout << formula << endl;
            } else {
                printError(r);
            }
        }
        else if (cmd == "vars") {
            vector<string> vars;
            Result r = tree.vars(vars);
            if (r.getCode() == OK) {
                for (int i = 0; i < static_cast<int>(vars.size()); i++) {
                    cout << vars[i] << " ";
                }
                cout << endl;
            } else {
                printError(r);
            }
        }
        else if (cmd == "comp") {
            string args;
            getline(iss, args);
            if (!args.empty() && args[0] == ' ') args.erase(0, 1);

            vector<double> vals;
            string current = "";

            for (int i = 0; i < static_cast<int>(args.length()); i++) {
                char c = args[i];

                if (c == ' ') {
                    if (!current.empty()) {
                        vals.push_back(atof(current.c_str()));
                        current = "";
                    }
                }
                else {
                    current += c;
                }
            }

            if (!current.empty())
                vals.push_back(atof(current.c_str()));

            double resultVal = 0.0;
            Result r = tree.comp(vals, resultVal);
            if (r.getCode() == OK) {
                cout << "wynik: " << resultVal << endl;
            } else {
                printError(r);
            }
        }
        else if (cmd == "join") {
            string f;
            getline(iss, f);
            if (!f.empty() && f[0] == ' ') f.erase(0, 1);
            Result r = tree.join(f);
            printError(r);
        }
        else if (cmd == "draw") {
            Result r = tree.draw();
            if (r.getCode() != OK) printError(r);
        }


        else {
            cout << "nieznana komenda! " << endl;
        }
    }
}



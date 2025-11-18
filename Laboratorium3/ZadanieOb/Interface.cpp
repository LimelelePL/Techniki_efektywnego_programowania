#include "Interface.h"
#include <sstream>
#include <iostream>

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
        cout << "> ";
        getline(cin, line);

        if (line == "exit")
            return;

        else if (line.substr(0, 5) == "enter") {
            string f = line.substr(6);
            tree.enter(f);
        }

        else if (line == "print") {
            tree.print();
        }

        else if (line == "vars") {
            tree.vars();
            cout << endl;
        }

        else if (line.substr(0, 4) == "comp") {

            string args = line.substr(5);
            stringstream ss(args);

            vector<double> vals;
            double v;

            while (ss >> v)
                vals.push_back(v);

            tree.comp(vals);
        }

        else if (line.substr(0, 4) == "join") {
            string f = line.substr(5);
            tree.join(f);
        }

        else {
            cout<<"nieznana komenda!" <<endl;
        }
    }
}
//
// Created by Dominik on 13.11.2025.
//


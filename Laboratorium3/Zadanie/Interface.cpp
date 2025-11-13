//
// Created by Dominik on 13.11.2025.
//

#include "Interface.h"

#include <iostream>
#include <sstream>
using namespace std;

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
        getline(cin, line);

        if (line == "exit") {
            return;
        }

        if (line.substr(0, 5) == "enter") {
            // pobieramy reszte ciagu od indexu 6
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

        else if (line.substr(0, 4) == "comp")
        {
            // od 5 znaku zaczynaja sie liczby
            string args = line.substr(5);

            vector<double> vals;
            string current = "";

            for (int i = 0; i < args.length(); i++)
            {
                char c = args[i];

                if (c == ' ') {
                    // po napotkaniu spacji resetujemy bufor
                    if (!current.empty()) {
                        vals.push_back(atof(current.c_str()));
                        current = "";
                    }
                }
                else {
                    // oddajemy znak
                    current += c;
                }
            }

            // ostatnia liczba
            if (!current.empty())
                vals.push_back(atof(current.c_str()));

            tree.comp(vals);
        }

        else if (line.substr(0, 4) == "join") {
            string f = line.substr(5);
            tree.join(f);
        }
        else cout<<"nieznana komenda! "<<endl;
    }
}



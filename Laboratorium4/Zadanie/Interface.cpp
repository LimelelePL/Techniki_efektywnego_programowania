#include "Interface.h"
#include <iostream>
#include <sstream>

#include "ResultSaver.h"
using namespace std;

void Interface::printError(Result<void, Error>& r)
{
    for (Error* e : r.getErrors())
        cout << "BLAD: " << e->getCode() << endl;
}
void Interface::printError(Result<string, Error>& r)
{
    for (Error* e : r.getErrors())
        cout << "BLAD: " << e->getCode() << endl;
}
void Interface::printError(Result<double, Error>& r)
{
    for (Error* e : r.getErrors())
        cout << "BLAD: " << e->getCode() << endl;
}

void Interface::run()
{
    string file = "C:/users/Dudek/OneDrive/Pulpit/Repozytoria/Techniki_efektywnego_programowania/Laboratorium4/Zadanie/file.txt";

    { // czyszczenie pliku po starcie programu
        std::ofstream clear(file, std::ios::trunc);
        clear.close();
    }

    string line;

    cout << "=== INTERFEJS DRZEWA FORMUL ===" << endl;
    cout << "Dostepne polecenia:" << endl;
    cout << " enter <formula>" << endl;
    cout << " print" << endl;
    cout << " vars" << endl;
    cout << " comp <v1> <v2> ..." << endl;
    cout << " join <formula>" << endl;
    cout << " exit" << endl;
    cout << " save " << endl;
    cout << "===============================" << endl;

    while (true)
    {
        cout << ">";
        if (!getline(cin, line)) return;

        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd.empty()) continue;
        if (cmd == "exit") return;

        if (cmd == "enter")
        {
            string formula;
            getline(iss, formula);
            if (!formula.empty() && formula[0] == ' ')
                formula.erase(0, 1);

            Result<void, Error> r = tree.enter(formula);

            if (!r.isSuccess()) {
                printError(r);
                ResultSaver<void>::save(r, file);
            }
        }

        else if (cmd == "print")
        {
            Result<string, Error> r = tree.print();
            if (r.isSuccess())
                cout << r.getValue() << endl;
            else {
                printError(r);
                ResultSaver<string> :: save(r, file);
            }
        }

        else if (cmd == "vars")
        {
            Result<string, Error> r = tree.vars();
            if (r.isSuccess())
            {
                for (auto& v : r.getValue())
                    cout << v << " ";
                cout << endl;
            }
            else {
                printError(r);
                ResultSaver<string> :: save(r, file);
            }
        }

        else if (cmd == "comp")
        {
            vector<double> vals;

            string rest;
            getline(iss, rest);
            if (!rest.empty() && rest[0] == ' ')
                rest.erase(0, 1);

            string tmp;
            for (int i = 0; i < (int)rest.size(); i++)
            {
                if (rest[i] == ' ')
                {
                    if (!tmp.empty())
                    {
                        vals.push_back(atof(tmp.c_str()));
                        tmp.clear();
                    }
                }
                else tmp += rest[i];
            }
            if (!tmp.empty()) vals.push_back(atof(tmp.c_str()));

            Result<double, Error> r = tree.comp(vals);
            if (r.isSuccess())
                cout << "wynik: " << r.getValue() << endl;
            else {
                printError(r);
                ResultSaver<double> :: save(r, file);
            }
        }

        else if (cmd == "join")
        {
            string formula;
            getline(iss, formula);
            if (!formula.empty() && formula[0] == ' ')
                formula.erase(0, 1);

            Result<void, Error> r = tree.join(formula);
            if (!r.isSuccess()) {
                printError(r);
                ResultSaver<void> :: save(r, file);
            }
        }

        else if (cmd == "save")
        {
            auto r = tree.exportTree();

            ResultSaver<Tree*>::save(r, file);

            cout << "Zapisano do tree.txt" << endl;
        }


        else
        {
            cout << "Nieznana komenda!" << endl;
        }
    }
}



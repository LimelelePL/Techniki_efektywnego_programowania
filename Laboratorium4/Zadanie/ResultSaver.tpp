#pragma once
#include <fstream>
#include <sstream>

#include "ResultSaver.h"

template<typename T>
void ResultSaver<T>::save(Result<T, Error> &r, const string &fileName) {
    if (r.isSuccess()) return;                // nie otwieramy pliku dla sukcesu
    std::ofstream f(fileName, std::ios::app);
    if (!f.is_open()) return;

    for (Error* e : r.getErrors()) {
        if (e) f << "BLAD: " << e->getCode() << "\n";
    }
    f.close();
}

inline void ResultSaver<void>::save(Result<void, Error> &r, const string &fileName) {
    if (r.isSuccess()) return;
    std::ofstream f(fileName, std::ios::app);
    if (!f.is_open()) return;

    for (Error* e : r.getErrors()) {
        if (e) f << "BLAD: " << e->getCode() << "\n";
    }
    f.close();
}

inline void ResultSaver<Tree*>::save(Result<Tree*, Error> &r, const string &fileName) {
    if (!r.isSuccess()) {
        std::ofstream f(fileName, std::ios::app);
        if (!f.is_open()) return;
        for (Error* e : r.getErrors()) {
            if (e) f << "BLAD: " << e->getCode() << "\n";
        }
        return;
    }

    Tree* tree = r.getValue();
    if (!tree) return;

    Result<string, Error> pr = tree->print();
    std::ofstream f(fileName, std::ios::app);
    if (!f.is_open()) return;

    if (pr.isSuccess()) {
        f << pr.getValue() << "\n";
    } else {
        for (Error* e : pr.getErrors()) {
            if (e) f << "BLAD: " << e->getCode() << "\n";
        }
    }
    f.close();
}
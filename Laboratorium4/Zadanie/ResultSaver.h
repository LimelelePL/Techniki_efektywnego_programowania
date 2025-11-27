// c++
#ifndef ZADANIE_RESULTSAVER_H
#define ZADANIE_RESULTSAVER_H

#include <string>
#include "Result.h"
#include "Error.h"
#include "Tree.h"

using std::string;

template <typename T>
class ResultSaver {
public:
    static void save(Result<T, Error> &r, const string& fileName);
};

template <>
class ResultSaver<void> {
public:
    static void save(Result<void, Error> &r, const string& fileName);
};

// specjalizacja dla Tree*
template <>
class ResultSaver<Tree*> {
public:
    static void save(Result<Tree*, Error> &r, const string& fileName);
};



#include "ResultSaver.tpp"

#endif // ZADANIE_RESULTSAVER_H





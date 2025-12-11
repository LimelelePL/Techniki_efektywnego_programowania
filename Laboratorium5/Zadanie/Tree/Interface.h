#ifndef INTERFACE_H
#define INTERFACE_H

#include "Tree.h"
#include "../Result/Result.h"
#include "../Result/Error.h"
#include <string>
#include <vector>

class Interface
{
public:
    void run();

private:
    Tree tree;

    void printError(Result<void, Error>& r);
    void printError(Result<string, Error>& r);
    void printError(Result<double, Error>& r);
};

#endif

//
// Created by Jonathan on 13/11/2017.
//

#ifndef COMPILADOR_SIMBOLO_H
#define COMPILADOR_SIMBOLO_H

#include <iostream>
#include <stdlib.h>

using  namespace std;

class Symbol
{
protected:
    char type;
    string symbol;
    string scope;
    char parameter;
    char parameterVector[30];
    bool function;

public:
    Symbol(char, string, string, bool);
    Symbol(char, string, string, char*, bool);
    void PrintSymbol();
    char GetSymbolType();
    string GetSymbol();
    string GetScope();
    char GetParameterVector(int);
    bool GetFunction();
    int GetParameterNumber();
};

#endif //COMPILADOR_SIMBOLO_H

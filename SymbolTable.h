//
// Created by Jonathan on 13/11/2017.
//

#ifndef COMPILADOR_SYMBOLTABLE_H
#define COMPILADOR_SYMBOLTABLE_H

#include "Simbolo.h"
#include <vector>

using namespace std;



class SymbolTable
{
public:
    SymbolTable();
    void AddSymbol(Symbol*);
    void PrintTable();
    bool FindSymbolInTable(string);
    bool FindSymbolInTable(string, string);
    Symbol* FindSymbol(string, string);

    char GetType(string, string);

    string GetVariableName(int);
    int GetSymbolLength();
};



#endif //COMPILADOR_SYMBOLTABLE_H

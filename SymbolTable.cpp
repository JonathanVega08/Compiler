//
// Created by Jonathan on 13/11/2017.
//

#include "SymbolTable.h"

vector<Symbol*> symbolVector;

SymbolTable::SymbolTable()
{

}

void SymbolTable::AddSymbol(Symbol *newSymbol)
{
    symbolVector.push_back(newSymbol);
}

void SymbolTable::PrintTable()
{
    for (int i = 0; i < symbolVector.size(); i++)
    {
        symbolVector[i]->PrintSymbol();
    }
    cout << endl;
}

bool SymbolTable::FindSymbolInTable(string idSymbol)
{
    for (int i = 0; i < symbolVector.size(); i++)
    {
        if( symbolVector[i]->GetSymbol() == idSymbol)
            return true;
    }
    return  false;
}

bool SymbolTable::FindSymbolInTable(string idSymbol, string scope)
{
    for (int i = 0; i < symbolVector.size(); i++)
    {
        if( symbolVector[i]->GetSymbol() == idSymbol && symbolVector[i]->GetScope() == scope)
            return true;
    }
    return  false;
}

Symbol* SymbolTable::FindSymbol(string id, string scope)
{
    for (int i = 0; i < symbolVector.size(); i++)
    {
        if (symbolVector[i]->GetSymbol() == id)
            return symbolVector[i];
    }
    return NULL;
}

char SymbolTable::GetType(string id, string scope)
{
    for (int i = 0; i < symbolVector.size(); i++)
    {
        if (symbolVector[i]->GetSymbol() == id and symbolVector[i]->GetScope() == scope)
            return symbolVector[i]->GetSymbolType();
    }
    return '@';
}

int SymbolTable::GetSymbolLength()
{
    return symbolVector.size();
}

string SymbolTable::GetVariableName(int index)
{
    return symbolVector[index]->GetSymbol();
}








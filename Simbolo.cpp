//
// Created by Jonathan on 13/11/2017.
//

#include "Simbolo.h"

Symbol::Symbol(char t, string s, string sc, bool f)
{
    this->type = t;
    this->symbol = s;
    this->scope = sc;
    this->function = f;
}

Symbol::Symbol(char t, string s, string sc, char *vP, bool f)
{
    this->type = t;
    this->symbol = s;
    this->scope = sc;
    this->function = f;

    for (int i = 0; i < sizeof(vP); i++)
    {
        this->parameterVector[i] = vP[i];
    }
}

void Symbol::PrintSymbol()
{
    cout << type << "  " << symbol << "  " << scope << endl << endl;
}

char Symbol::GetSymbolType()
{
    return type;
}

string Symbol::GetSymbol()
{
    return symbol;
}

string Symbol::GetScope()
{
    return  scope;
}

bool Symbol::GetFunction()
{
    return function;
}

char Symbol::GetParameterVector(int i)
{
    return parameterVector[i];
}

int Symbol::GetParameterNumber()
{
    int i;
    for (i = 0; i < sizeof(parameterVector); i++)
    {
        if(parameterVector[i] == 0)
        {
            return  i;
        }
    }

    return i;
}
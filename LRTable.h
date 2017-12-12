//
// Created by Jonathan on 12/11/2017.
//

#ifndef COMPILADOR_LRTABLE_H
#define COMPILADOR_LRTABLE_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <ctype.h>

using  namespace std;

class LR_Table
{
public:
    int rows;
    int columns;
    int rulesQty;

    vector<int> RulesId;
    vector<int> RulesLength;
    vector<vector<int>> Matrix;
    vector<int> Rules;
    vector<int> matrixNumber;

    vector<string> NotTerminalAux;
    vector<string> NotTerminal;

    LR_Table();

    void ReadFile(char *);
    void FillInformation();
    void PrintMatrix();
    void PrintRulesId();
    void PrintRulesLength();
    void PrintNotTerminals();
};

#endif //COMPILADOR_LRTABLE_H

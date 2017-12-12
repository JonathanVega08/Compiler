//
// Created by Jonathan on 27/11/2017.
//

#ifndef COMPILADOR_SINTACTICO_H
#define COMPILADOR_SINTACTICO_H

#include <vector>
#include "Lexico.h"
#include "LRTable.h"
#include "Stack.h"



class Sintactico
{
public:
    Stack stack;
    Lexical lexical;

    int action, row, column;

    vector<string> terminalsAndNotTerminals;
    LR_Table lr_table;

    Sintactico();
    void Print();
    void Process();
};

#endif //COMPILADOR_SINTACTICO_H

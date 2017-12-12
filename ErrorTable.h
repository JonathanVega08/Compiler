//
// Created by Jonathan on 25/11/2017.
//

#ifndef COMPILADOR_ERRORTABLE_H
#define COMPILADOR_ERRORTABLE_H

#include <iostream>
#include <vector>

using  namespace std;

class ErrorTable
{
protected:
    vector<string> errorVector;

public:
    ErrorTable();
    void InsertError(int, string);
    void ShowErrorVector();

};
#endif //COMPILADOR_ERRORTABLE_H

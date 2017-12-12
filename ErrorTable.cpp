//
// Created by Jonathan on 25/11/2017.
//

#include "ErrorTable.h"

ErrorTable::ErrorTable()
{

}

void ErrorTable::InsertError(int errorId, string error)
{
    string errorDescription = "";

    switch (errorId)
    {
        case 1:
            cout << "\tError: " << errorId << " \"" << error << "\" la variable fue definida anteriormente" << endl;
            errorDescription = "\tError: 1 \""  + error + "\" la variable fue definida anteriormente";
            break;

        case 2:
            cout << "\tError: " << errorId << " \"" << error << "\" la variable no ha sido definida" << endl;
            errorDescription = "\tError: 2 \""  + error + "\" la variable no ha sido definida";
            break;

        case 3:
            cout << "\tError: " << errorId << " conversion invalida, la expresion no es del mismo tipo" << endl;
            errorDescription = "\tError: 3 conversion invalida, la expresion no es del mismo tipo";
            break;

        case 4:
            cout << "\tError: " << errorId << " conversion invalida, la expresion no es del mismo tipo que" << error << endl;
            errorDescription = "\tError: 4 conversion invalida, la expresion no es del mismo tipo que" + error;
            break;

        case 5:
            cout << "\tError: " << errorId << ", la funcion" " \"" << error << "\" fue definida anteriormente" << endl;
            errorDescription = "\tError: 5, la funcion \"" + error + "\" fue definida anteriormente";
            break;

        case 6:
            cout << "\tError: " << errorId << ", el valor que regresa es diferente al de la funcion" " \"" << error << "\"" << endl;
            errorDescription = "\tError: 6, el valor que regresa es diferente al de la funcion \"" + error + "\"";
            break;

        case 7:
            cout << "\tError: " << errorId << "la cantidad de argumentos no son validis para la definicion de la funcion" << endl;
            errorDescription = "\tError: 7 la cantidad de argumentos no son validis para la definicion de la funcion";
            break;

        case 8:
            cout << "\tError: " << errorId << "la cantidad de argumentos no coincide con la declaracion de la funcion"<< endl;
            errorDescription = "\tError: 8 la cantidad de argumentos no coincide con la declaracion de la funcion";
            break;
    }

    errorVector.push_back(errorDescription);
}

void ErrorTable::ShowErrorVector()
{
    cout << "  ERRORES ENCONTRADOS :  " << endl;
    for (int i = 0; i < errorVector.size(); i++)
    {
        cout << errorVector[i] << endl;
    }
}

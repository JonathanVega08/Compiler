//
// Created by Jonathan on 12/11/2017.
//

#include "LRTable.h"

LR_Table::LR_Table()
{
    rows = 0;
    columns = 0;
}

void LR_Table::ReadFile(char *fileName)
{
    long int longIntAux;
    char *lineEnd;
    int lineLength;

    string fileContent;
    locale local;

    ifstream file(fileName);

    getline(file, fileContent, '\n');
    lineLength = atoi(fileContent.c_str());

    int lineAux = lineLength;

    Rules.push_back(lineLength);

    for (int i = 0; i < lineAux; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (j == 2)
            {
                getline(file, fileContent, '\n');

                longIntAux = strtol(fileContent.c_str(),&lineEnd,10);
                if (lineEnd == fileContent)
                    NotTerminalAux.push_back(fileContent);

                continue;
            }

            getline(file, fileContent, '\t');

            if (file.eof())
                break;

            lineLength = atoi(fileContent.c_str());

            Rules.push_back(lineLength);
        }
    }

    getline(file, fileContent, '\t');
    rows = atoi(fileContent.c_str());

    getline(file, fileContent, '\n');
    columns = atoi(fileContent.c_str());

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (j == columns - 1)
            {
                getline(file, fileContent, '\n');
                lineLength = atoi(fileContent.c_str());
                matrixNumber.push_back(lineLength);
                continue;
            }

            getline(file, fileContent, '\t');
            lineLength = atoi(fileContent.c_str());
            matrixNumber.push_back(lineLength);
        }
    }

    file.close();

    FillInformation();
}

void LR_Table::FillInformation()
{
    rulesQty = Rules[0];

    RulesId.resize(rulesQty);
    RulesLength.resize(rulesQty);
    NotTerminal.resize(rulesQty);
    Matrix.resize(rows);

    for (int i = 0; i < rows; i++)
    {
        Matrix[i].resize(columns);
    }

    for (int i = 0; i < rulesQty; i++)
    {
        RulesId[i] = Rules[(2*i) + 1];
        RulesLength[i] = Rules[(2*i) + 2];
    }

    int contAux = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            Matrix[i][j] = matrixNumber[contAux];
            contAux++;
        }
    }
}

void LR_Table::PrintMatrix()
{
    cout << endl;
    cout << "Matriz de reglas[" << rows << "][" << columns << "] = " << endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << Matrix[i][j] << ", \t";
        }
        cout << endl;
    }
}

void LR_Table::PrintRulesId()
{
    cout << "Rules ID:  " << rulesQty << endl;

    for (int i = 0; i < rulesQty; i++)
    {
        cout << RulesId[i] << ",";
    }
}

void LR_Table::PrintRulesLength()
{
    cout << "Rules Length:  " << rulesQty << endl;

    for (int i = 0; i < rulesQty; i++)
    {
        cout << RulesLength[i] << ",";
    }
}

void LR_Table::PrintNotTerminals()
{
    cout << "No Terminales:  " << rulesQty << endl;

    for (int i = 0; i < rulesQty; i++)
    {
        cout << NotTerminalAux[i] << ",";
    }
}

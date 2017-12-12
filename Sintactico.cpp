//
// Created by Jonathan on 27/11/2017.
//

#include "Sintactico.h"
#include "CodeGeneration.h"

Sintactico::Sintactico()
{
    lr_table.ReadFile((char*)"gramatica.lr");
    action = 0;
    //lr_table.PrintMatrix();
}

void Sintactico::Print()
{
    stack.PrintElement();

    cout << "Fila: " << row << " Columna: " << column << endl;
    cout << "Entrada: " << lexical.symbol << endl;
    cout << "Accion: " << action << endl;
    cout << endl << endl;
}

void Sintactico::Process()
{
    bool aceptation = false;

    lexical.input("entrada.txt");

    stack.Push(new Terminal("$"));
    stack.Push(new Status(0));

    lexical.nextSymbol();

    row = stack.Top()->GetStatus();
    column = lexical.type;
    action = lr_table.Matrix[row][column];

    while(true)
    {
        if (action == -1)
        {
            cout << "Aceptacion" << endl;
            break;
        }
        if (action > 0)
        {
            stack.Push(new Terminal(lexical.symbol));
            stack.Push(new Status(action));
            lexical.nextSymbol();

            row = stack.Top()->GetStatus();
            column = lexical.type;
            action = lr_table.Matrix[row][column];
        }
        else if (action < 0)
        {
            int opc = (action*-1)-1;
            int oldAction = 0;

            Node* newNode;

            switch (opc)
            {
                case 2:
                case 7:
                case 10:
                case 12:
                case 15:
                case 19:
                case 26:
                case 29:
                case 31:
                case 33:
                    newNode = new NullNode();
                    break;

                case 1:
                    newNode = new Rule1_Program(stack);
                    newNode->Print(1);
                    newNode->GenerateCode();
                    break;

                case 3:
                    newNode = new Rule3_Declaration(stack);
                    break;

                case 4:
                    newNode = new Rule4_Definition(stack);
                    break;

                case 5:
                    newNode = new Rule5_Definition(stack);
                    break;

                case 6:
                    newNode = new Rule6_DefVar(stack);
                    break;

                case 8:
                    newNode = new Rule8_VariableList(stack);
                    break;

                case 9:
                    newNode = new Rule9_FunctionDef(stack);
                    break;

                case 11:
                    newNode = new Rule11_Parameters(stack);
                    break;

                case 13:
                    newNode = new Rule13_ParameterList(stack);
                    break;

                case 14:
                    newNode = new Rule14_FunctionBlock(stack);
                    break;

                case 16:
                    newNode = new Rule16_LocalDefinition(stack);
                    break;

                case 17:
                    newNode = new Rule17_LocalDef(stack);
                    break;

                case 18:
                    newNode = new Rule18_LocalDef(stack);
                    break;

                case 20:
                    newNode = new Rule20_Sentences(stack);
                    break;

                case 21:
                    newNode = new Rule21_Sentence(stack);
                    break;

                case 22:
                    newNode = new Rule22_Sentence(stack);
                    break;

                case 23:
                    newNode = new Rule23_Sentence(stack);
                    break;

                case 24:
                    newNode = new Rule24_Sentence(stack);
                    break;

                case 25:
                    newNode = new Rule25_Sentence(stack);
                    break;

                case 27:
                    newNode = new Rule27_Else(stack);
                    break;

                case 28:
                    newNode = new Rule28_Block(stack);
                    break;

                case 30:
                    newNode = new Rule30_ReturnedValue(stack);
                    break;

                case 32:
                    newNode = new Rule32_Arguments(stack);
                    break;

                case 34:
                    newNode = new Rule34_ArgumentList(stack);
                    break;

                case 35:
                    newNode = new Rule35_End(stack);
                    break;

                case 36:
                    newNode = new Rule36_End(stack);
                    break;

                case 37:
                    newNode = new Rule37_End(stack);
                    break;

                case 38:
                    newNode = new Rule38_End(stack);
                    break;

                case 39:
                    newNode = new Rule39_End(stack);
                    break;

                case 40:
                    newNode = new Rule40_FunctionCall(stack);
                    break;

                case 41:
                    newNode = new Rule41_BlockSentence(stack);
                    break;

                case 42:
                    newNode = new Rule42_BlockSentence(stack);
                    break;

                case 43:
                    newNode = new Rule43_Expression(stack);
                    break;

                case 44:
                    newNode = new Rule44_Expression(stack);
                    break;

                case 45:
                    newNode = new Rule45_Expression(stack);
                    break;

                case 46:
                    newNode = new Rule46_Expression(stack);
                    break;

                case 47:
                    newNode = new Rule47_Expression(stack);
                    break;

                case 48:
                    newNode = new Rule48_Expression(stack);
                    break;

                case 49:
                    newNode = new Rule49_Expression(stack);
                    break;

                case 50:
                    newNode = new Rule50_Expression(stack);
                    break;

                case 51:
                    newNode = new Rule51_Expression(stack);
                    break;

                case 52:
                    newNode = new Rule52_Expression(stack);
                    break;
            }

            row = stack.Top()->GetStatus();
            column = lr_table.RulesId[(-action)-2];
            oldAction = action;
            action = lr_table.Matrix[row][column];

            stack.Push(new NotTerminal(lr_table.NotTerminalAux[(-oldAction)-2], newNode));
            stack.Push(new Status(action));

            cout << endl;

            row = stack.Top()->GetStatus();
            column = lexical.type;
            action = lr_table.Matrix[row][column];
            continue;
        }
        else
            break;
    }
}

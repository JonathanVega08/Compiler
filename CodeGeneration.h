//
// Created by Jonathan on 25/11/2017.
//

#ifndef COMPILADOR_CODEGENERATION_H
#define COMPILADOR_CODEGENERATION_H
#include <fstream>
#include <sstream>
#include "Stack.h"
#include "SymbolTable.h"
#include "ErrorTable.h"


SymbolTable *symbolTable = new SymbolTable();
ErrorTable *errorTable = new ErrorTable();

char parameterVector[20];
char argsVector[20];
int parameterQty;
int argsQty;

int labelQty = 0;

class Node
{
protected:
    char nodeType;
    string scope;

public:
    virtual void Print(int t){}
    virtual char ValidateType(string){}
    virtual void ValidateType(char, string){}
    virtual string GenerateCode(){}

    void Name(int t, string name)
    {
        for (int i = 0; i < t-1; i++)
        {
            cout << "   ";
        }

        cout << name << endl;
    }

    void Terminal(int t, string terminal)
    {
        for (int i = 0; i < t; i++)
        {
            cout << "   ";
        }

        cout << terminal << endl;
    }

    string JumpExpresion(string relOperator)
    {
        string jumpExpression = "";

        if (relOperator == ">")
            jumpExpression = "jg";
        else if (relOperator == "<")
            jumpExpression = "jl";
        else if (relOperator == ">=")
            jumpExpression = "jge";
        else if (relOperator == "<=")
            jumpExpression = "jle";
        else if (relOperator == "==")
            jumpExpression = "je";
        else if (relOperator == "!=")
            jumpExpression = "jne";

        return jumpExpression;
    }

    string GetNumberOfLabel()
    {
        stringstream label;
        label << labelQty;

        return  label.str();
    }
};

class NullNode : public Node
{
protected:
    Node *nullNode;

public:
    NullNode()
    {
        nullNode = NULL;
    }

    void Print(int t)
    {
        Name(t, "Null");
    }

    char ValidateType(string s)
    {
        cout << "" << endl;
    }

    string GenerateCode()
    {
        return "";
    }
};

class Rule1_Program : public Node
{
protected:
    Node* definition;

public:
    Rule1_Program(Stack &s)
    {
        scope = "global";
        s.Pop();
        definition = ((NotTerminal*)s.Top())->GetNode();
        delete(s.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Programa_R1>");
        definition->Print(t+1);
        Name(t, "</Programa_R1>");
        ValidateType(scope);
        symbolTable->PrintTable();
        errorTable->ShowErrorVector();
    }

    char ValidateType(string scope)
    {
        definition->ValidateType(scope);
    }

    string GenerateCode()
    {
        string assemblyDefaultInfo;

        assemblyDefaultInfo = ".386\n.model flat, stdcall\noption casemap:none\n";
        assemblyDefaultInfo += "include \\masm32\\macros\\macros.asm\ninclude \\masm32\\include\\masm32.inc\ninclude \\masm32\\include\\kernel32.inc\n";
        assemblyDefaultInfo += "includelib \\masm32\\lib\\masm32.lib\nincludelib \\masm32\\lib\\kernel32.lib\n\n";
        assemblyDefaultInfo += ".data\n";

        for (int i = 0; i < symbolTable->GetSymbolLength(); i++)
        {
            if (symbolTable->FindSymbol(symbolTable->GetVariableName(i), "global")->GetFunction())
            {
                cout << "\t\t\t fue una funcion y no la pongo en .data !!!!!!!!!!!!!! " << endl;
                continue;
            }
            else
            {
                assemblyDefaultInfo += symbolTable->GetVariableName(i) + " dword 0\n";
            }
        }

        assemblyDefaultInfo += "\n.code\n";

        assemblyDefaultInfo += definition->GenerateCode();

        cout << assemblyDefaultInfo << endl;

        ofstream assemblyFile("output.asm");

        if(assemblyFile.is_open())
        {
            assemblyFile << assemblyDefaultInfo;
        }

        assemblyFile.close();
    }
};

class Rule3_Declaration : public Node
{
protected:
    Node *definition;
    Node *definitions;

public:
    Rule3_Declaration(Stack &stack)
    {
        stack.Pop();
        definition = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        definitions = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Definiciones_R3>");
        definition->Print(t+1);
        definitions->Print(t+1);
        Name(t, "</Definiciones_R3>");
    }

    char ValidateType(string scope)
    {
        definitions->ValidateType(scope);
        definition->ValidateType(scope);
    }

    string GenerateCode()
    {
        string code;

        code = definitions->GenerateCode();
        code += definition->GenerateCode();
        return code;
    }
};

class Rule4_Definition : public  Node
{
protected:
    Node * variableDeclaration;

public:
    Rule4_Definition(Stack &stack)
    {
        stack.Pop();
        variableDeclaration = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Definicion_R4>");
        variableDeclaration->Print(t+1);
        Name(t, "</Definicion_R4>");
    }

    char ValidateType(string scope)
    {
        variableDeclaration->ValidateType(scope);
    }

    string GenerateCode()
    {
        return variableDeclaration->GenerateCode();
    }
};

class Rule5_Definition : public Node
{
protected:
    Node * functionDef;

public:
    Rule5_Definition(Stack &stack)
    {
        stack.Pop();
        functionDef = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Definicion_R5>");
        functionDef->Print(t+1);
        Name(t, "</Definicion_R5>");
    }

    char ValidateType(string scope)
    {
        functionDef->ValidateType(scope);
    }

    string GenerateCode()
    {
        return functionDef->GenerateCode();
    }
};

class Rule6_DefVar : public Node
{
protected:
    string idVariable;
    string variableType;
    Node *variableList;

public:
    Rule6_DefVar(Stack &stack)
    {
        stack.Pop();
        stack.Pop();
        stack.Pop();

        variableList = (stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();

        idVariable = stack.Top()->GetTerminal();
        delete(stack.Pop());
        stack.Pop();

        variableType = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<DefVar_R6>");
        Terminal(t, variableType);
        Terminal(t, idVariable);
        variableList->Print(t+1);
        Name(t, "</DefVar_R6>");
    }

    char ValidateType(string scope)
    {
        if (!symbolTable->FindSymbolInTable(idVariable, scope))
        {
            nodeType = variableType[0];
            Symbol *symbol = new Symbol(nodeType, idVariable, scope, false);
            symbolTable->AddSymbol(symbol);
        }
        else
        {
            errorTable->InsertError(1, idVariable);
        }
        variableList->ValidateType(nodeType, scope);
    }

    string GenerateCode()
    {
        return "";
    }
};

class Rule8_VariableList : public Node
{
protected:
    Node * variableList;
    string idVariable;

public:
    Rule8_VariableList(Stack &stack)
    {
        stack.Pop();
        variableList = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        idVariable = stack.Top()->GetTerminal();
        delete(stack.Pop());
        stack.Pop();
        stack.Pop();
    }

    void Print(int t)
    {
        Name(t, "<ListaVar_R8>");
        Terminal(t, idVariable);
        variableList->Print(t+1);
        Name(t, "</DefVar_R8>");
    }

    void ValidateType(char nodeType, string scope)
    {
        if (!symbolTable->FindSymbolInTable(idVariable))
        {
            Symbol *symbol = new Symbol(nodeType, idVariable, scope, false);
            symbolTable->AddSymbol(symbol);
        }
        else
        {
            errorTable->InsertError(1, idVariable);
        }
        variableList->ValidateType(nodeType, scope);
    }

    string GenerateCode()
    {
        return "";
    }
};

class Rule9_FunctionDef : public Node
{
protected:
    Node *parameters;
    Node *block;
    string functionType;
    string idFunction;

public:
    Rule9_FunctionDef(Stack &stack)
    {
        stack.Pop();
        block = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        stack.Pop();
        stack.Pop();
        parameters = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        stack.Pop();
        stack.Pop();
        idFunction = stack.Top()->GetTerminal();
        delete(stack.Pop());
        stack.Pop();
        functionType = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<DefFunc_R9>");
        Terminal(t, functionType);
        Terminal(t, idFunction);
        parameters->Print(t+1);
        block->Print(t+1);
        Name(t, "</DefFunc_R9>");
    }

    char ValidateType(string scope)
    {
        if (!symbolTable->FindSymbolInTable(idFunction))
        {
            for (int i = 0; i < 20; i++)
            {
                parameterVector[i] = 0;
            }
            parameterQty = 0;
            nodeType = functionType[0];
        }
        else
        {
            errorTable->InsertError(1, idFunction);
        }

        parameters->ValidateType(idFunction);

        Symbol *symbol = new Symbol(nodeType, idFunction, scope, parameterVector, true);
        symbolTable->AddSymbol(symbol);
        block->ValidateType(idFunction);
    }

    string GenerateCode()
    {
        string code;
        code = idFunction + ":\n";
        code += parameters->GenerateCode();
        code += block->GenerateCode();
        code += "print str$(eax)\nprint chr$(10)\nexit\n";
        code += "end " + idFunction + "\n";

        return code;
    }
};

class Rule11_Parameters : public Node
{
protected:
    Node* parameterList;
    string id;
    string type;

public:
    Rule11_Parameters(Stack &stack)
    {
        stack.Pop();
        parameterList = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        id = stack.Top()->GetTerminal();
        delete(stack.Pop());
        stack.Pop();
        type = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Parametros_R11>");
        Terminal(t, type);
        Terminal(t, id);
        parameterList->Print(t+1);
        Name(t, "</Parametros_R11>");
    }

    char ValidateType(string scope)
    {
        if (!symbolTable->FindSymbolInTable(id, scope))
        {
            nodeType = type[0];
            Symbol *symbol = new Symbol(nodeType, id, scope, false);
            symbolTable->AddSymbol(symbol);
            parameterVector[parameterQty++] = nodeType;
        }
        else
        {
            errorTable->InsertError(1, id);
        }

        parameterList->ValidateType(nodeType, scope);
    }

    string GenerateCode()
    {
        return parameterList->GenerateCode();
    }
};

class Rule13_ParameterList : public Node
{
protected:
    Node* parameterList;
    string id;
    string type;

public:
    Rule13_ParameterList(Stack &stack)
    {
        stack.Pop();
        parameterList = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        id = stack.Top()->GetTerminal();
        delete(stack.Pop());
        stack.Pop();
        type = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Parametros_R11>");
        Terminal(t, type);
        Terminal(t, id);
        parameterList->Print(t+1);
        Name(t, "</Parametros_R11>");
    }

    char ValidateType(string scope)
    {
        if (!symbolTable->FindSymbolInTable(id, scope))
        {
            nodeType = type[0];
            Symbol *symbol = new Symbol(nodeType, id, scope, false);
            symbolTable->AddSymbol(symbol);
            parameterVector[parameterQty++] = nodeType;
        }
        else
        {
            errorTable->InsertError(1, id);
        }

        parameterList->ValidateType(nodeType, scope);
    }

    string GenerateCode()
    {
        return "";
    }
};

class Rule14_FunctionBlock : public Node
{
protected:
    Node * localScope;
public:
    Rule14_FunctionBlock(Stack &stack)
    {
        stack.Pop();
        stack.Pop();
        stack.Pop();
        localScope = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        stack.Pop();
    }

    void Print(int t)
    {
        Name(t, "<BloqueFuncion_R14>");
        localScope->Print(t+1);
        Name(t, "</BloqueFuncion_R14>");
    }

    char ValidateType(string scope)
    {
        localScope->ValidateType(scope);
    }

    string GenerateCode()
    {
        return localScope->GenerateCode();
    }
};

class Rule16_LocalDefinition : public Node
{
protected:
    Node *localDefinition;
    Node *localDefinitions;

public:
    Rule16_LocalDefinition(Stack &stack)
    {
        stack.Pop();
        localDefinitions = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        localDefinition = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<DefLocales_R16>");
        localDefinition->Print(t+1);
        localDefinitions->Print(t+1);
        Name(t, "</DefLocales_R16>");
    }

    char ValidateType(string scope)
    {
        localDefinition->ValidateType(scope);
        localDefinitions->ValidateType(scope);
    }

    string GenerateCode()
    {
        string code;

        code = localDefinition->GenerateCode();
        code += localDefinitions->GenerateCode();
        return code;
    }
};

class Rule17_LocalDef : public Node
{
protected:
    Node * localDef;

public:
    Rule17_LocalDef(Stack &stack)
    {
        stack.Pop();
        localDef = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<DefLocal_R17>");
        localDef->Print(t+1);
        Name(t, "</DefLocal_R17>");
    }

    char ValidateType(string scope)
    {
        localDef->ValidateType(scope);
    }

    string GenerateCode()
    {
        return localDef->GenerateCode();
    }
};

class Rule18_LocalDef : public Node
{
protected:
    Node * sentence;

public:
    Rule18_LocalDef(Stack &stack)
    {
        stack.Pop();
        sentence = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<DefLocal_R18>");
        sentence->Print(t+1);
        Name(t, "</DefLocal_R18>");
    }

    char ValidateType(string scope)
    {
        sentence->ValidateType(scope);
    }

    string GenerateCode()
    {
        return sentence->GenerateCode();
    }
};

class Rule20_Sentences : public Node
{
protected:
    Node *sentence;
    Node *sentences;

public:
    Rule20_Sentences(Stack &stack)
    {
        stack.Pop();
        sentences = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        sentence = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Sentencias_R20>");
        sentence->Print(t+1);
        sentences->Print(t+1);
        Name(t, "</Sentencias_R20>");
    }

    char ValidateType(string scope)
    {
        sentence->ValidateType(scope);
        sentences->ValidateType(scope);
    }

    string GenerateCode()
    {
        string code;

        code = sentence->GenerateCode();
        code += sentences->GenerateCode();
        return code;
    }
};

class Rule21_Sentence : public Node
{
protected:
    Node* expression;
    string id;
    string equalValidation;

public:
    Rule21_Sentence(Stack &stack)
    {
        stack.Pop();
        stack.Pop();
        stack.Pop();
        expression = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        equalValidation = stack.Top()->GetTerminal();
        delete(stack.Pop());
        stack.Pop();
        id = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Sentencia_R21>");
        Terminal(t, id);
        Terminal(t, equalValidation);
        expression->Print(t+1);
        Name(t, "</Sentencia_R21>");
    }

    char ValidateType(string scope)
    {
        char expressionType = expression->ValidateType(scope);

        cout << "\tTipo: " << expressionType << "vs" << symbolTable->GetType(id, scope) << endl;

        if (!symbolTable->FindSymbolInTable(id))
        {
            errorTable->InsertError(2, id);
        }
        else if (expressionType == symbolTable->GetType(id, scope))
        {
            cout << "La sentencia es del mismo tipo" << endl;
            return expressionType;
        }
        else if((symbolTable->GetType(id,"global") != '@') && (symbolTable->GetType(id, "global") == expressionType))
        {
            cout << "La sentencia es del mismo tipo" << endl;
            return expressionType;
        }
        else
        {
            errorTable->InsertError(4, id);
        }
    }

    string GenerateCode()
    {
        string code;
        code = expression->GenerateCode();
        code += "pop eax\nmov " + id + ", eax\n";
        return code;
    }
};

class Rule22_Sentence : public Node
{
protected:
    Node* elseBlock;
    Node* blockSentence;
    Node* expression;
    string ifSentence;
    string equalValidation;

public:
    Rule22_Sentence(Stack &stack)
    {
        stack.Pop();
        elseBlock = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        blockSentence = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        stack.Pop();
        stack.Pop();
        expression = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        stack.Pop();
        stack.Pop();
        ifSentence = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Sentencia_R22>");
        Terminal(t, ifSentence);
        expression->Print(t+1);
        blockSentence->Print(t+1);
        elseBlock->Print(t+1);
        Name(t, "</Sentencia_R22>");
    }

    char ValidateType(string scope)
    {
        expression->ValidateType(scope);
        blockSentence->ValidateType(scope);
        elseBlock->ValidateType(scope);
    }

    string GenerateCode()
    {
        labelQty++;
        string code, labelInfo;

        code = expression->GenerateCode();
        code += "pop eax\ncmp eax,0\n";
        code += "je If_" + GetNumberOfLabel() + "\n";
        labelInfo = "If_" + GetNumberOfLabel();
        code += blockSentence->GenerateCode();
        code += labelInfo + ":\n";
        code += elseBlock->GenerateCode();

        return code;
    }
};

class Rule23_Sentence : public Node
{
protected:
    Node* block;
    Node* expression;
    string whileExp;

public:
    Rule23_Sentence(Stack &stack)
    {
        stack.Pop();
        block = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        stack.Pop();
        stack.Pop();
        expression = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        stack.Pop();
        stack.Pop();
        whileExp = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Sentencia_R23>");
        Terminal(t, whileExp);
        expression->Print(t+1);
        block->Print(t+1);
        Name(t, "</Sentencia_R23>");
    }

    char ValidateType(string scope)
    {
        expression->ValidateType(scope);
        block->ValidateType(scope);
    }

    string GenerateCode()
    {
        return  "";
    }
};

class Rule24_Sentence : public Node
{
protected:
    Node* returnValue;
    string returnExp;

public:
    Rule24_Sentence(Stack &stack)
    {
        stack.Pop();
        stack.Pop();
        stack.Pop();
        returnValue = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        returnExp = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Sentencia_R24>");
        Terminal(t, returnExp);
        returnValue->Print(t+1);
        Name(t, "</Sentencia_R23>");
    }

    char ValidateType(string scope)
    {
        char returnVal = returnValue->ValidateType(scope);

        if (returnVal != symbolTable->GetType(scope, "global"))
            errorTable->InsertError(6, "");
    }

    string GenerateCode()
    {
        return "ret\n";
    }
};

class Rule25_Sentence : public Node
{
protected:
    Node* functionCall;

public:
    Rule25_Sentence(Stack &stack)
    {
        stack.Pop();
        stack.Pop();
        stack.Pop();
        functionCall = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Sentencia_R25>");
        functionCall->Print(t+1);
        Name(t, "</Sentencia_R23>");
    }

    char ValidateType(string scope)
    {
        functionCall->ValidateType(scope);
    }

    string GenerateCode()
    {
        return functionCall->GenerateCode();
    }
};

class Rule27_Else : public Node
{
protected:
    Node* blockSentence;
    string elseExp;

public:
    Rule27_Else(Stack &stack)
    {
        stack.Pop();
        blockSentence = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        elseExp = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Else_R27>");
        Terminal(t, elseExp);
        blockSentence->Print(t+1);
        Name(t, "</Else_R27>");
    }

    char ValidateType(string scope)
    {
        blockSentence->ValidateType(scope);
    }

    string GenerateCode()
    {
        return blockSentence->GenerateCode();
    }
};

class Rule28_Block : public Node
{
protected:
    Node* sentence;
public:
    Rule28_Block(Stack &stack)
    {
        stack.Pop();
        stack.Pop();
        stack.Pop();
        sentence = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        stack.Pop();
    }

    void Print(int t)
    {
        Name(t, "<Bloque_R28>");
        sentence->Print(t+1);
        Name(t, "</Bloque_R28>");
    }

    char ValidateType(string scope)
    {
        sentence->ValidateType(scope);
    }

    string GenerateCode()
    {
        return sentence->GenerateCode();
    }
};

class Rule30_ReturnedValue : public Node
{
protected:
    Node* expression;
public:
    Rule30_ReturnedValue(Stack &stack)
    {
        stack.Pop();
        expression = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Bloque_R28>");
        expression->Print(t+1);
        Name(t, "</Bloque_R28>");
    }

    char ValidateType(string scope)
    {
        expression->ValidateType(scope);
    }

    string GenerateCode()
    {
        return expression->GenerateCode();
    }
};

class Rule32_Arguments : public Node
{
protected:
    Node* argsList;
    Node* expression;

public:
    Rule32_Arguments(Stack &stack)
    {
        stack.Pop();
        argsList = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        expression = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Argumentos_R32>");
        expression->Print(t+1);
        argsList->Print(t+1);
        Name(t, "</Argumentos_R32>");
    }

    char ValidateType(string scope)
    {
        char expType = expression->ValidateType(scope);
        argsVector[argsQty++] = expType;
        argsList->ValidateType(scope);
    }

    string GenerateCode()
    {
        string code;

        code = expression->GenerateCode();
        code += argsList->GenerateCode();
        return  code;
    }
};

class Rule34_ArgumentList : public Node
{
protected:
    Node* argsList;
    Node* expression;

public:
    Rule34_ArgumentList(Stack &stack)
    {
        stack.Pop();
        argsList = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        expression = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        stack.Pop();
    }

    void Print(int t)
    {
        Name(t, "<ListaArgumentos_R34>");
        expression->Print(t+1);
        argsList->Print(t+1);
        Name(t, "</ListaArgumentos_R34>");
    }

    char ValidateType(string scope)
    {
        char expType = expression->ValidateType(scope);
        argsVector[argsQty++] = expType;
        argsList->ValidateType(scope);
    }

    string GenerateCode()
    {
        string code;

        code = expression->GenerateCode();
        code += argsList->GenerateCode();
        return  code;
    }
};

class Rule35_End : public Node
{
protected:
    Node* functionCall;

public:
    Rule35_End(Stack &stack)
    {
        stack.Pop();
        functionCall = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Termino_R35>");
        functionCall->Print(t+1);
        Name(t, "</Termino_R35>");
    }

    char ValidateType(string scope)
    {
        functionCall->ValidateType(scope);
    }

    string GenerateCode()
    {
        return functionCall->GenerateCode();
    }
};

class Rule36_End : public Node
{
protected:
    string id;

public:
    Rule36_End(Stack &stack)
    {
        stack.Pop();
        id = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Termino_R36>");
        Terminal(t, id);
        Name(t, "</Termino_R36>");
    }

    char ValidateType(string scope)
    {
        if (!symbolTable->FindSymbolInTable(id, scope))
        {
            if (symbolTable->FindSymbolInTable(id, "global"))
            {
                cout << "tipo de Termino_R36:  "<< id << " "  << symbolTable->GetType(id,"global")<< endl;
                return symbolTable->GetType(id,"global");
            }
            else
                errorTable->InsertError(2, id);
        }
        cout << "tipo de Termino_R36:  "<< id << " "  << symbolTable->GetType(id, scope)<< endl;
        return symbolTable->GetType(id, scope);
    }

    string GenerateCode()
    {
        return "push "+id+"\n";
    }
};

class Rule37_End : public Node
{
protected:
    string integer;

public:
    Rule37_End(Stack &stack)
    {
        stack.Pop();
        integer = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Termino_R37>");
        Terminal(t, integer);
        Name(t, "</Termino_R38>");
    }

    char ValidateType(string scope)
    {
        if (!symbolTable->FindSymbolInTable(integer, scope))
        {
            cout << "tipo de Termino_R37:  "<< integer << " "  << 'i' << endl;
            return 'i';
        }
    }

    string GenerateCode()
    {
        return "push "+ integer +"\n";
    }
};

class Rule38_End : public Node
{
protected:
    string real;

public:
    Rule38_End(Stack &stack)
    {
        stack.Pop();
        real = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Termino_R38>");
        Terminal(t, real);
        Name(t, "</Termino_R38>");
    }

    char ValidateType(string scope)
    {
        if (!symbolTable->FindSymbolInTable(real, scope))
        {
            cout << "tipo de Termino_R38:  "<< real << " "  << 'f' << endl;
            return 'f';
        }
    }

    string GenerateCode()
    {
        return "push "+ real +"\n";
    }
};


class Rule39_End : public Node
{
protected:
    string cadena;

public:
    Rule39_End(Stack &stack)
    {
        stack.Pop();
        cadena = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Termino_R39>");
        Terminal(t, cadena);
        Name(t, "</Termino_R39>");
    }

    char ValidateType(string scope)
    {
        if (!symbolTable->FindSymbolInTable(cadena, scope))
        {
            cout << "tipo de Termino_R39:  "<< cadena << " "  << 's' << endl;
            return 's';
        }
    }

    string GenerateCode()
    {
        return "push "+ cadena +"\n";
    }
};

class Rule40_FunctionCall : public Node
{
protected:
    Node* args;
    string id;

public:
    Rule40_FunctionCall(Stack &stack)
    {
        stack.Pop();
        stack.Pop();
        stack.Pop();
        args = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        stack.Pop();
        stack.Pop();
        id = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<LlamadaFunc_R40>");
        Terminal(t, id);
        args->Print(t+1);
        Name(t, "</LlamadaFunc_R40>");
    }

    char ValidateType(string scope)
    {
        for (int i = 0; i < 20; i++)
            argsVector[i] = 0;

        argsQty = 0;

        if (symbolTable->FindSymbolInTable(id, "global"))
        {
            args->ValidateType(scope);

            int paramQty = symbolTable->FindSymbol(id, scope)->GetParameterNumber();
            if (paramQty != argsQty)
            {
                errorTable->InsertError(7, id);
            }
            else
            {
                for (int i = 0; i < paramQty; i++)
                {
                    if (symbolTable->FindSymbol(id, scope)->GetParameterVector(i) != argsVector[i])
                        errorTable->InsertError(8, id);
                }
            }
            return symbolTable->GetType(id, "global");
        }
        else
        {
            errorTable->InsertError(5, id);
        }
    }

    string GenerateCode()
    {
        return "";
    }
};

class Rule41_BlockSentence : public Node
{
protected:
    Node* sentence;
public:
    Rule41_BlockSentence(Stack &stack)
    {
        stack.Pop();
        sentence = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Sentencia_R41>");
        sentence->Print(t+1);
        Name(t, "</Sentencia_R41>");
    }

    char ValidateType(string scope)
    {
        return  sentence->ValidateType(scope);
    }

    string GenerateCode()
    {
        return sentence->GenerateCode();
    }
};

class Rule42_BlockSentence : public Node
{
protected:
    Node* block;
public:
    Rule42_BlockSentence(Stack &stack)
    {
        stack.Pop();
        block = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<SentenciaBloque_R42>");
        block->Print(t+1);
        Name(t, "</SentenciaBloque_R42>");
    }

    char ValidateType(string scope)
    {
        return  block->ValidateType(scope);
    }

    string GenerateCode()
    {
        return block->GenerateCode();
    }
};

class Rule43_Expression : public Node
{
protected:
    Node* expression;
public:
    Rule43_Expression(Stack &stack)
    {
        stack.Pop();
        stack.Pop();
        stack.Pop();
        expression = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        stack.Pop();
    }

    void Print(int t)
    {
        Name(t, "<Expresion_R43>");
        expression->Print(t+1);
        Name(t, "</Expresion_R43>");
    }

    char ValidateType(string scope)
    {
        return  expression->ValidateType(scope);
    }

    string GenerateCode()
    {
        return expression->GenerateCode();
    }
};

class Rule44_Expression : public Node
{
protected:
    Node* expression;
    string addOp;
public:
    Rule44_Expression(Stack &stack)
    {
        stack.Pop();
        expression = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        addOp = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Expresion_R44>");
        Terminal(t, addOp);
        expression->Print(t+1);
        Name(t, "</Expresion_R44>");
    }

    char ValidateType(string scope)
    {
        return  expression->ValidateType(scope);
    }

    string GenerateCode()
    {
        string code;
        code = expression->GenerateCode();
        if(addOp == "-"){
            code += "pop eax\n";
            code += "neg eax\n";
            code += "push eax\n";
        }
        return code;
    }
};

class Rule45_Expression : public Node
{
protected:
    Node* expression;
    string notOp;
public:
    Rule45_Expression(Stack &stack)
    {
        stack.Pop();
        expression = ((NotTerminal*)stack.Top())->GetNode();
        delete(stack.Pop());
        stack.Pop();
        notOp = stack.Top()->GetTerminal();
        delete(stack.Pop());
    }

    void Print(int t)
    {
        Name(t, "<Expresion_R45>");
        Terminal(t, notOp);
        expression->Print(t+1);
        Name(t, "</Expresion_R45>");
    }

    char ValidateType(string scope)
    {
        return  expression->ValidateType(scope);
    }

    string GenerateCode()
    {
        return  expression->GenerateCode();
    }
};

class Rule46_Expression : public Node {
protected:
    Node *leftExpression;
    string operatorType;
    Node *rightExpression;

public:
    Rule46_Expression(Stack &stack) {
        stack.Pop();
        rightExpression = ((NotTerminal *) stack.Top())->GetNode();
        delete (stack.Pop());
        stack.Pop();
        operatorType = stack.Top()->GetTerminal();
        delete (stack.Pop());
        stack.Pop();
        leftExpression = ((NotTerminal *) stack.Top())->GetNode();
        delete (stack.Pop());
    }

    void Print(int t) {
        Name(t, "<Expresion_R46>");
        leftExpression->Print(t + 1);
        Terminal(t, operatorType);
        rightExpression->Print(t + 1);
        Name(t, "</Expresion_R46>");
    }

    char ValidateType(string scope)
    {
        char leftType = leftExpression->ValidateType(scope);
        char rightType = rightExpression->ValidateType(scope);

        if (leftType == rightType)
        {
            cout << "EXPRESION 46 SON DEL MISMO TIPO \n" <<  endl;
            return leftType;
        }
        else
            errorTable->InsertError(3, "");
    }

    string GenerateCode()
    {
        string code;
        code = leftExpression->GenerateCode();
        code += rightExpression->GenerateCode();
        if(operatorType == "*")
            code += "pop ebx\npop eax\nxor edx,edx\nimul ebx\npush eax\n";
        else
            code += "pop ebx\npop eax\nxor edx,edx\nidiv ebx\npush eax\n";
        return code;
    }
};

class Rule47_Expression : public Node {
protected:
    Node *leftExpression;
    string operatorType;
    Node *rightExpression;

public:
    Rule47_Expression(Stack &stack) {
        stack.Pop();
        rightExpression = ((NotTerminal *) stack.Top())->GetNode();
        delete (stack.Pop());
        stack.Pop();
        operatorType = stack.Top()->GetTerminal();
        delete (stack.Pop());
        stack.Pop();
        leftExpression = ((NotTerminal *) stack.Top())->GetNode();
        delete (stack.Pop());
    }

    void Print(int t) {
        Name(t, "<Expresion_R47>");
        leftExpression->Print(t + 1);
        Terminal(t, operatorType);
        rightExpression->Print(t + 1);
        Name(t, "</Expresion_R47>");
    }

    char ValidateType(string scope)
    {
        char leftType = leftExpression->ValidateType(scope);
        char rightType = rightExpression->ValidateType(scope);

        if (leftType == rightType)
        {
            cout << "EXPRESION 47 SON DEL MISMO TIPO \n" <<  endl;
            return leftType;
        }
        else
            errorTable->InsertError(3, "");
    }

    string GenerateCode()
    {
        string code;
        code = leftExpression->GenerateCode();
        code += rightExpression->GenerateCode();
        if(operatorType == "+")
            code += "pop ebx\npop eax\nadd eax, ebx\npush eax\n";
        else
            code += "pop ebx\npop eax\nsub eax, ebx\npush eax\n";
        return code;
    }
};

class Rule48_Expression : public Node {
protected:
    Node *leftExpression;
    string operatorType;
    Node *rightExpression;

public:
    Rule48_Expression(Stack &stack) {
        stack.Pop();
        rightExpression = ((NotTerminal *) stack.Top())->GetNode();
        delete (stack.Pop());
        stack.Pop();
        operatorType = stack.Top()->GetTerminal();
        delete (stack.Pop());
        stack.Pop();
        leftExpression = ((NotTerminal *) stack.Top())->GetNode();
        delete (stack.Pop());
    }

    void Print(int t) {
        Name(t, "<Expresion_R48>");
        leftExpression->Print(t + 1);
        Terminal(t, operatorType);
        rightExpression->Print(t + 1);
        Name(t, "</Expresion_R48>");
    }

    char ValidateType(string scope)
    {
        char leftType = leftExpression->ValidateType(scope);
        char rightType = rightExpression->ValidateType(scope);

        if (leftType == rightType)
        {
            cout << "EXPRESION 48 SON DEL MISMO TIPO \n" <<  endl;
            return leftType;
        }
        else
            errorTable->InsertError(3, "");
    }

    string GenerateCode()
    {
        string code;
        labelQty++;

        code = leftExpression->GenerateCode();
        code += rightExpression->GenerateCode();
        code += "pop ebx\npop eax\n";
        code += "cmp eax, ebx\n";
        code += JumpExpresion(operatorType) + " True_" + GetNumberOfLabel() + "\n";
        code += "push 0\njmp End_" + GetNumberOfLabel() + "\n";
        code += "True_"+ GetNumberOfLabel() + ":\n";
        code += "push 1\n";
        code += "End_"+ GetNumberOfLabel() + ":";
        return code;
    }
};

class Rule49_Expression : public Node {
protected:
    Node *leftExpression;
    string operatorType;
    Node *rightExpression;

public:
    Rule49_Expression(Stack &stack) {
        stack.Pop();
        rightExpression = ((NotTerminal *) stack.Top())->GetNode();
        delete (stack.Pop());
        stack.Pop();
        operatorType = stack.Top()->GetTerminal();
        delete (stack.Pop());
        stack.Pop();
        leftExpression = ((NotTerminal *) stack.Top())->GetNode();
        delete (stack.Pop());
    }

    void Print(int t) {
        Name(t, "<Expresion_R49>");
        leftExpression->Print(t + 1);
        Terminal(t, operatorType);
        rightExpression->Print(t + 1);
        Name(t, "</Expresion_R49>");
    }

    char ValidateType(string scope)
    {
        char leftType = leftExpression->ValidateType(scope);
        char rightType = rightExpression->ValidateType(scope);

        if (leftType == rightType)
        {
            cout << "EXPRESION 49 SON DEL MISMO TIPO \n" <<  endl;
            return leftType;
        }
        else
            errorTable->InsertError(3, "");
    }

    string GenerateCode()
    {
        string code = "";
        return code;
    }
};

class Rule50_Expression : public Node {
protected:
    Node *leftExpression;
    string operatorType;
    Node *rightExpression;

public:
    Rule50_Expression(Stack &stack) {
        stack.Pop();
        rightExpression = ((NotTerminal *) stack.Top())->GetNode();
        delete (stack.Pop());
        stack.Pop();
        operatorType = stack.Top()->GetTerminal();
        delete (stack.Pop());
        stack.Pop();
        leftExpression = ((NotTerminal *) stack.Top())->GetNode();
        delete (stack.Pop());
    }

    void Print(int t) {
        Name(t, "<Expresion_R50>");
        leftExpression->Print(t + 1);
        Terminal(t, operatorType);
        rightExpression->Print(t + 1);
        Name(t, "</Expresion_R50>");
    }

    char ValidateType(string scope)
    {
        char leftType = leftExpression->ValidateType(scope);
        char rightType = rightExpression->ValidateType(scope);

        if (leftType == rightType)
        {
            cout << "EXPRESION 50 SON DEL MISMO TIPO \n" <<  endl;
            return leftType;
        }
        else
            errorTable->InsertError(3, "");
    }

    string GenerateCode()
    {
        string code = "";
        return code;
    }
};

class Rule51_Expression : public Node {
protected:
    Node *leftExpression;
    string operatorType;
    Node *rightExpression;

public:
    Rule51_Expression(Stack &stack) {
        stack.Pop();
        rightExpression = ((NotTerminal *) stack.Top())->GetNode();
        delete (stack.Pop());
        stack.Pop();
        operatorType = stack.Top()->GetTerminal();
        delete (stack.Pop());
        stack.Pop();
        leftExpression = ((NotTerminal *) stack.Top())->GetNode();
        delete (stack.Pop());
    }

    void Print(int t) {
        Name(t, "<Expresion_R51>");
        leftExpression->Print(t + 1);
        Terminal(t, operatorType);
        rightExpression->Print(t + 1);
        Name(t, "</Expresion_R51>");
    }

    char ValidateType(string scope)
    {
        char leftType = leftExpression->ValidateType(scope);
        char rightType = rightExpression->ValidateType(scope);

        if (leftType == rightType)
        {
            cout << "EXPRESION 51 SON DEL MISMO TIPO \n" <<  endl;
            return leftType;
        }
        else
            errorTable->InsertError(3, "");
    }

    string GenerateCode()
    {
        string code = "";
        return code;
    }
};

class Rule52_Expression : public Node {
protected:
    Node *finished;

public:
    Rule52_Expression(Stack &stack) {
        stack.Pop();
        finished = ((NotTerminal *) stack.Top())->GetNode();
        delete (stack.Pop());
    }

    void Print(int t) {
        Name(t, "<Expresion_R52>");
        finished->Print(t + 1);
        Name(t, "</Expresion_R52>");
    }

    char ValidateType(string scope)
    {
        return finished->ValidateType(scope);
    }

    string GenerateCode()
    {
        return finished->GenerateCode();
    }
};
#endif //COMPILADOR_CODEGENERATION_H

//
// Created by Jonathan on 12/11/2017.
//
#include "Lexico.h"
#include <fstream>

Lexical::Lexical(string source)
{
    index = 0;
    this->source = source;
    symbolBelongs = true;
}

Lexical::Lexical()
{
    index = 0;
    symbolBelongs = true;
}

string Lexical::getSymbolType(int type)
{
    string symbolType;

    switch (type)
    {
        case SymbolType::IDENTIFIER:
            symbolType = "Identificador";
            break;

        case SymbolType::INTEGER:
            symbolType = "Entero";
            break;

        case SymbolType::FLOAT:
            symbolType = "Real";
            break;

        case SymbolType::STRING:
            symbolType = "Cadena";
            break;

        case SymbolType::FUNCTION_TYPE:
            symbolType = "Tipo";
            break;

        case SymbolType::ADD_OPERATOR:
            symbolType = "opSuma";
            break;

        case SymbolType::MUL_OPERATOR:
            symbolType = "opMul";
            break;

        case SymbolType::RELATIONAL_OPERATOR:
            symbolType = "opRelac";
            break;

        case SymbolType::OR_OPERATOR:
            symbolType = "opOr";
            break;

        case SymbolType::AND_OPERATOR:
            symbolType = "opAnd";
            break;

        case SymbolType::NOT_OPERATOR:
            symbolType = "opNot";
            break;

        case SymbolType::EQUALS_OPERATOR:
            symbolType = "opIgualdad";
            break;

        case SymbolType::SEMICOLON:
            symbolType = ";";
            break;

        case SymbolType::COMMA:
            symbolType = ",";
            break;

        case SymbolType::LEFT_PARENTHESES:
            symbolType = "(";
            break;

        case SymbolType::RIGHT_PARENTHESES:
            symbolType = ")";
            break;

        case SymbolType::LEFT_CURLY_BRACKET:
            symbolType = "{";
            break;

        case SymbolType::RIGHT_CURLY_BRACKET:
            symbolType = "}";
            break;

        case SymbolType::ASSIGN_OPERATOR:
            symbolType = "=";
            break;

        case SymbolType::RESERVED_IF:
            symbolType = "if";
            break;

        case SymbolType::RESERVED_WHILE:
            symbolType = "while";
            break;

        case SymbolType::RESERVED_RETURN:
            symbolType = "return";
            break;

        case SymbolType::RESERVED_ELSE:
            symbolType = "else";
            break;

        case SymbolType::END_OF_STRING:
            symbolType = "END";
            break;

        default:
            symbolType = "ERROR";
            break;
    }

    return symbolType;
}

void Lexical::input(string source)
{
    ifstream file(source);
    char cadena [1000];

    if(!file.good())
    {


    } else
    {
        file.getline((char*)&cadena, 1000,file.eof());
        file.close();
    }

    index = 0;
    this->source = (char*)cadena;
    cout << cadena << endl;
}



int Lexical::nextSymbol()
{
    status = 0;
    continueAnalysis = true;
    symbol.clear();

    /*while (continueAnalysis)
    {
        if (symbolBelongs)
            c = nextChar();
        symbolBelongs = true;
        switch (status)
        {
            case 0:
                if (isLetter(c))
                    nextStatus(21);
                else if (isDigit(c))
                    nextStatus(1);
                else if (isAdition(c))
                    aceptation(6);
                else if (isMultiplication(c))
                    aceptation(7);
                else if (isGreaterThan(c) || isLowerThan(c))
                    nextStatus(4);
                else if (isVerticalBar(c))
                    nextStatus(8);
                else if (isAmpersand(c))
                    nextStatus(10);
                else if (isExclamation(c))
                    nextStatus(12);
                else if (isEqualSymbol(c))
                    nextStatus(14);
                else if (isSemicolon(c))
                    aceptation(15);
                else if (isComma(c))
                    aceptation(16);
                else if (isLeftParentheses(c))
                    aceptation(17);
                else if (isRightParentheses(c))
                    aceptation(18);
                else if (isLeftCB(c))
                    aceptation(19);
                else if (isRightCB(c))
                    aceptation(20);
                else if (isDollar(c))
                    aceptation(23);
                else if (isSpaceBar(c))
                {
                    //symbolBelongs = false;
                    nextStatus(0);
                }
                else if (isQuotationMark(c))
                    nextStatus(22);
                else
                    aceptation(-1);
                break;

            case 1:
                if (isDigit(c))
                    nextStatus(1);
                else if (isPeriod(c))
                    nextStatus(2);
                else
                {
                    symbolBelongs = false;
                    aceptation(1);
                }
                break;
            case 2:
                if (isDigit(c))
                    nextStatus(3);
                else
                {
                    symbolBelongs = false;
                    aceptation(-1);
                }
                break;
            case 3:
                if (isDigit(c))
                    nextStatus(3);
                else
                {
                    symbolBelongs = false;
                    aceptation(2);
                }
                break;
            case 4:
                if (isEqualSymbol(c))
                    aceptation(5);
                else
                {
                    symbolBelongs = false;
                    aceptation(5);
                }
                break;
            case 8:
                if (isVerticalBar(c))
                    aceptation(9);
                else
                {
                    symbolBelongs = false;
                    aceptation(-1);
                }
                break;
            case 10:
                if (isAmpersand(c))
                    aceptation(11);
                else
                {
                    symbolBelongs = false;
                    aceptation(-1);
                }
                break;
            case 12:
                if (isEqualSymbol(c))
                    aceptation(13);
                else
                {
                    symbolBelongs = false;
                    aceptation(12);
                }
                break;
            case 14:
                if (isEqualSymbol(c))
                    aceptation(13);
                else
                {
                    symbolBelongs = false;
                    aceptation(14);
                }
                break;

            case 21:
                if (isLetter(c) || isDigit(c))
                    nextStatus(21);
                else
                {
                    symbolBelongs = false;
                    aceptation(21);
                }
                break;
            case 22:
                if (isQuotationMark(c))
                    aceptation(24);
                else if (isascii(c))
                    nextStatus(21);
                break;
            default:
                break;
        }
    }*/

    while (continueAnalysis)
    {
        if (symbolBelongs)
            c = nextChar();
        symbolBelongs = true;
        switch (status)
        {
            case 0:
                if (isLetter(c))
                    nextStatus(1);
                else if
                        (isDigit(c))
                    nextStatus(3);
                else if (isAdition(c))
                    aceptation(5);
                else if (isMultiplication(c))
                    aceptation(6);
                else if (isGreaterThan(c) || isLowerThan(c))
                    nextStatus(6);
                else if (isVerticalBar(c))
                    nextStatus(7);
                else if (isAmpersand(c))
                    nextStatus(8);
                else if (isExclamation(c))
                    nextStatus(9);
                else if (isEqualSymbol(c))
                    nextStatus(10);
                else if (isSemicolon(c))
                    aceptation(12);
                else if (isComma(c))
                    aceptation(13);
                else if (isLeftParentheses(c))
                    aceptation(14);
                else if (isRightParentheses(c))
                    aceptation(15);
                else if (isLeftCB(c))
                    aceptation(16);
                else if (isRightCB(c))
                    aceptation(17);
                else if (isDollar(c))
                    aceptation(23);
                else if (isSpaceBar(c))
                    nextStatus(0);
                else if (isQuotationMark(c))
                    nextStatus(11);
                else
                    aceptation(-1);
                break;

            case 1:
                if (isLetter(c))
                    nextStatus(1);
                else if (isDigit(c))
                    nextStatus(2);
                else
                {
                    symbolBelongs = false;

                    aceptation(checkString());
                }
                break;

            case 2:
                if (isLetter(c) || isDigit(c))
                    nextStatus(2);
                else
                {
                    symbolBelongs = false;
                    aceptation(0);
                }
                break;
            case 3:
                if (isDigit(c))
                    nextStatus(3);
                else if (isPeriod(c))
                    nextStatus(4);
                else
                {
                    symbolBelongs = false;
                    aceptation(1);
                }
                break;
            case 4:
                if (isDigit(c))
                    nextStatus(5);
                else
                {
                    symbolBelongs = false;
                    aceptation(-1);
                }
                break;
            case 5:
                if (isDigit(c))
                    nextStatus(5);
                else
                {
                    symbolBelongs = false;
                    aceptation(2);
                }
                break;
            case 6:
                if (isEqualSymbol(c))
                    aceptation(7);
                else
                {
                    symbolBelongs = false;
                    aceptation(7);
                }
                break;
            case 7:
                if (isVerticalBar(c))
                    aceptation(8);
                else
                {
                    symbolBelongs = false;
                    aceptation(-1);
                }
                break;
            case 8:
                if (isAmpersand(c))
                    aceptation(9);
                else
                {
                    symbolBelongs = false;
                    aceptation(-1);
                }
                break;
            case 9:
                if (isEqualSymbol(c))
                    aceptation(11);
                else
                {
                    symbolBelongs = false;
                    aceptation(10);
                }
                break;
            case 10:
                if (isEqualSymbol(c))
                    aceptation(11);
                else
                {
                    symbolBelongs = false;
                    aceptation(18);
                }
                break;
            case 11:
                if (isQuotationMark(c))
                    aceptation(3);
                else if (isascii(c))
                    nextStatus(11);
                break;
            default:
                break;
        }
    }

    /*switch (status)
    {
        case 1:
            type = SymbolType::INTEGER;
            break;

        case 3:
            type = SymbolType::FLOAT;
            break;

        case 4:
        case 5:
            type = SymbolType::RELATIONAL_OPERATOR;
            break;

        case 6:
            type = SymbolType::ADD_OPERATOR;
            break;

        case 7:
            type = SymbolType::MUL_OPERATOR;
            break;

        case 9:
            type = SymbolType::OR_OPERATOR;
            break;

        case 11:
            type = SymbolType::AND_OPERATOR;
            break;

        case 12:
            type = SymbolType::NOT_OPERATOR;
            break;

        case 13:
            type = SymbolType::EQUALS_OPERATOR;
            break;

        case 14:
            type = SymbolType::ASSIGN_OPERATOR;
            break;

        case 15:
            type = SymbolType::SEMICOLON;
            break;

        case 16:
            type = SymbolType::COMMA;
            break;

        case 17:
            type = SymbolType::LEFT_PARENTHESES;
            break;

        case 18:
            type = SymbolType::RIGHT_PARENTHESES;
            break;

        case 19:
            type = SymbolType::LEFT_CURLY_BRACKET;
            break;

        case 20:
            type = SymbolType::RIGHT_PARENTHESES;
            break;

        case 21:
            if (symbol == "int" || symbol == "float" || symbol == "void" || symbol == "string")
                type = SymbolType::FUNCTION_TYPE;
            else if (symbol == "if")
                type = SymbolType::RESERVED_IF;
            else if (symbol == "while")
                type = SymbolType::RESERVED_WHILE;
            else if (symbol == "return")
                type = SymbolType::RESERVED_RETURN;
            else if (symbol == "else")
                type = SymbolType::RESERVED_ELSE;
            else
                type = SymbolType::IDENTIFIER;
            break;

        case 23:
            type = SymbolType::END_OF_STRING;
            break;

        case 24:
            type = SymbolType::STRING;
            break;

        default:
            type = SymbolType::ERROR;
            break;
    }*/

    switch (status)
    {
        case 0:
            type = SymbolType::IDENTIFIER;
            break;

        case 1:
            type = SymbolType::INTEGER;
            break;

        case 2:
            type = SymbolType::FLOAT;
            break;

        case 3:
            type = SymbolType::STRING;
            break;

        case 4:
            type = SymbolType::FUNCTION_TYPE;
            break;

        case 5:
            type = SymbolType::ADD_OPERATOR;
            break;

        case 6:
            type = SymbolType::MUL_OPERATOR;
            break;

        case 7:
            type = SymbolType::RELATIONAL_OPERATOR;
            break;

        case 8:
            type = SymbolType::OR_OPERATOR;
            break;

        case 9:
            type = SymbolType::AND_OPERATOR;
            break;

        case 10:
            type = SymbolType::NOT_OPERATOR;
            break;

        case 11:
            type = SymbolType::EQUALS_OPERATOR;
            break;

        case 12:
            type = SymbolType::SEMICOLON;
            break;

        case 13:
            type = SymbolType::COMMA;
            break;

        case 14:
            type = SymbolType::LEFT_PARENTHESES;
            break;

        case 15:
            type = SymbolType::RIGHT_PARENTHESES;
            break;

        case 16:
            type = SymbolType::LEFT_CURLY_BRACKET;
            break;

        case 17:
            type = SymbolType::RIGHT_CURLY_BRACKET;
            break;

        case 18:
            type = SymbolType::ASSIGN_OPERATOR;
            break;

        case 19:
            type = SymbolType::RESERVED_IF;
            break;

        case 20:
            type = SymbolType::RESERVED_WHILE;
            break;

        case 21:
            type = SymbolType::RESERVED_RETURN;
            break;

        case 22:
            type = SymbolType::RESERVED_ELSE;
            break;

        case 23:
            type = SymbolType::END_OF_STRING;
            break;

        default:
            type = SymbolType::ERROR;

    }

    return type;
}

char Lexical::nextChar()
{
    if (finished())
        return '$';
    return source[index++];
}

void Lexical::nextStatus(int status)
{
    this->status = status;

    if (symbolBelongs && !isSpaceBar(c))
        symbol += c;
}

void Lexical::aceptation(int status)
{
    nextStatus(status);
    continueAnalysis = false;
}

bool Lexical::finished()
{
    return index >= source.length();
}

bool Lexical::isLetter(char c)
{
    return isalpha(c) || c == '_';
}

bool Lexical::isQuotationMark(char c)
{
    return c == '"';
}

bool Lexical::isDigit(char c)
{
    return isdigit(c);
}

bool Lexical::isSpaceBar(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

bool Lexical::isColon(char c)
{
    return c == ':';
}

bool Lexical::isSemicolon(char c)
{
    return c == ';';
}

bool Lexical::isComma(char c)
{
    return c == ',';
}

bool Lexical::isAdition(char c)
{
    return c == '+' || c == '-';
}

bool Lexical::isMultiplication(char c)
{
    return c == '*' || c == '/';
}

bool Lexical::isLeftCB(char c)
{
    return c == '{';
}

bool Lexical::isRightCB(char c)
{
    return c == '}';
}

bool Lexical::isPeriod(char c)
{
    return c == '.';
}

bool Lexical::isLeftParentheses(char c)
{
    return c == '(';
}

bool Lexical::isRightParentheses(char c)
{
    return c == ')';
}

bool Lexical::isGreaterThan(char c)
{
    return c == '>';
}

bool Lexical::isLowerThan(char c)
{
    return c == '<';
}

bool Lexical::isEqualSymbol(char c)
{
    return c == '=';
}

bool Lexical::isExclamation(char c)
{
    return c == '!';
}

bool Lexical::isVerticalBar(char c)
{
    return c == '|';
}

bool Lexical::isAmpersand(char c)
{
    return c == '&';
}

bool Lexical::isDollar(char c)
{
    return c == '$';
}

void Lexical::goBack()
{
    if (c != '$')
        index--;
    continueAnalysis = false;
}

int Lexical::checkString()
{
    if (symbol == "int" || symbol == "float" || symbol == "void")
        return 4;
    else if (symbol == "if")
        return 19;
    else if (symbol == "while")
        return 20;
    else if (symbol == "return")
        return 21;
    else if (symbol == "else")
        return 22;
    else
        return 0;
}



//
// Created by Jonathan on 12/11/2017.
//

#ifndef COMPILADOR_LEXICO_H
#define COMPILADOR_LEXICO_H

#include <iostream>
#include <string>

using namespace std;

class SymbolType
{
public:
    static const int ERROR = -1;
    static const int IDENTIFIER = 0;
    static const int INTEGER = 1;
    static const int FLOAT = 2;
    static const int STRING = 3;
    static const int FUNCTION_TYPE = 4;
    static const int ADD_OPERATOR = 5;
    static const int MUL_OPERATOR = 6;
    static const int RELATIONAL_OPERATOR = 7;
    static const int OR_OPERATOR = 8;
    static const int AND_OPERATOR = 9;
    static const int NOT_OPERATOR = 10;
    static const int EQUALS_OPERATOR = 11;
    static const int SEMICOLON = 12;
    static const int COMMA = 13;
    static const int LEFT_PARENTHESES = 14;
    static const int RIGHT_PARENTHESES = 15;
    static const int LEFT_CURLY_BRACKET = 16;
    static const int RIGHT_CURLY_BRACKET = 17;
    static const int ASSIGN_OPERATOR = 18;
    static const int RESERVED_IF = 19;
    static const int RESERVED_WHILE = 20;
    static const int RESERVED_RETURN = 21;
    static const int RESERVED_ELSE = 22;
    static const int END_OF_STRING = 23;

};

class Lexical
{
private:
    string source;

    int index;
    bool continueAnalysis;
    bool symbolBelongs;
    char c;
    int status;

    char nextChar();
    void nextStatus(int status);
    void aceptation(int status);
    void goBack();
    int checkString();

    bool isLetter(char c);
    bool isDigit(char c);
    bool isSpaceBar(char c);
    bool isColon(char c);
    bool isSemicolon(char c);
    bool isComma(char c);
    bool isAdition(char c);
    bool isMultiplication(char c);
    bool isLeftCB(char c);
    bool isRightCB(char c);
    bool isPeriod(char c);
    bool isLeftParentheses(char c);
    bool isRightParentheses(char c);
    bool isGreaterThan(char c);
    bool isLowerThan(char c);
    bool isEqualSymbol(char c);
    bool isExclamation(char c);
    bool isVerticalBar(char c);
    bool isAmpersand(char c);
    bool isDollar(char c);
    bool isQuotationMark(char c);

public:
    string symbol;
    int type;
    Lexical(string source);
    Lexical();

    void input(string source);
    string getSymbolType(int type);

    int nextSymbol();
    bool finished();
};

#endif //COMPILADOR_LEXICO_H

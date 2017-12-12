//
// Created by Jonathan on 12/11/2017.
//

#ifndef COMPILADOR_STACK_H
#define COMPILADOR_STACK_H

#include <list>
#include <string>
#include <iostream>

using namespace std;

class Node;

class StackElement
{
public:
    virtual void PrintElement(){};
    virtual int GetStatus(){};
    virtual string GetTerminal(){};
    virtual  Node* GetNode(){};
};

class Terminal : public StackElement
{
protected:
    string terminal;
public:
    Terminal(string terminal)
    {
        this->terminal = terminal;
    }

    string GetTerminal()
    {
        return  this->terminal;
    }

    void PrintElement()
    {
        cout << terminal << " ";
    }
};

class NotTerminal : public StackElement
{
protected:
    string notTerminal;
    Node* node;

public:
    NotTerminal(string notTerminal, Node* newNode)
    {
        this->notTerminal = notTerminal;
        this->node = newNode;
    }

    string GetNotTerminal()
    {
        return  this->notTerminal;
    }

    Node* GetNode()
    {
        return this->node;
    }

    void PrintElement()
    {
        cout << notTerminal << " ";
    }
};

class Status : public StackElement
{
protected:
    int status;
public:
    Status(int status)
    {
        this->status = status;
    }

    int GetStatus()
    {
        return this->status;
    }

    void PrintElement()
    {
        cout << status << " ";
    }
};

class Stack
{
private:
    list <StackElement*> elementList;

public:
    void Push(StackElement*);
    StackElement* Top();
    StackElement* Pop();
    void PrintElement();
};


#endif //COMPILADOR_STACK_H

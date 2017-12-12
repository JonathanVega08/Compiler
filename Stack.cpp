//
// Created by Jonathan on 12/11/2017.
//
#include "Stack.h"

void Stack::Push(StackElement *newElement)
{
    elementList.push_front(newElement);
}

StackElement* Stack::Pop()
{
    StackElement* elementToErase = *elementList.begin();
    elementList.erase(elementList.begin());

    return elementToErase;
}

StackElement* Stack::Top()
{
    return *elementList.begin();
}

void Stack::PrintElement()
{
    list <StackElement*>::reverse_iterator i;
    StackElement *x;

    cout << "Stack:  " << endl;

    for (i = elementList.rbegin(); i != elementList.rend(); i++)
    {
        x = *i;
        x->PrintElement();
    }

    cout << endl;
}


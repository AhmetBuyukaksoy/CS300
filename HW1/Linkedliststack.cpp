#include "Linkedliststack.h"
#include <iostream>
using namespace std;

template <typename T>
void Linkedliststack<T> :: push(T d)
{
    // creating a new node
    node<T> *temp = new node<T>();
    // setting data to it
    temp->data = d;

    // add the node in front of list
    if(front == NULL)
    {
        temp->next = NULL;
    }
    else
    {
        temp->next = front;
    }
    front = temp;
}

template <typename T>
void Linkedliststack<T> :: pop()
{
    // this should print when creating the maze.
    if(front == NULL)
        cout << "UNDERFLOW\n";
    
    // delete the element on top of the stack
    else
    {
        node<T> *temp = front;
        front = front->next;
        delete(temp);
    }
}

template <typename T>
T Linkedliststack<T> :: top()
{
    return front->data;
}

template <typename T>
bool Linkedliststack<T> :: empty()
{
    return front == nullptr;
}


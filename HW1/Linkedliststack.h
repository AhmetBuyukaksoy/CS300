
#ifndef linkedliststack_h
#define linkedliststack_h

#include <iostream>
using namespace std;

template <typename T>
struct node
{
    T data;
    node *next;
};


template <typename T>
class Linkedliststack
{
    node<T>* front;  // points to the head of list
    public:
    // default constructor
    Linkedliststack()
    {
        front = NULL;
    }
    // push method to add data element
    void push(T);
    // pop method to remove data element
    void pop();
    // top method to return top data element
    T top();
    // check if stack is empty
    bool empty();
};



#endif /* linkedliststack_h */


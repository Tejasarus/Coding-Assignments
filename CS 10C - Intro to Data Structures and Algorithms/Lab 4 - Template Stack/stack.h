#include <string>
#ifndef STACK_H
#define STACK_H
#include <iostream>

#include <stdexcept>
using namespace std;


template<typename T>
class stack
{
    
    public:
    stack();
    void push(T val);
    void pop();
    T top();
    bool empty();

    private:
    static const int MAX_SIZE = 20;
    T arr[MAX_SIZE];
    int size;

};
template<typename A>
stack<A>::stack()
{
    size = 0; //just set the size to 0
}
template<typename B>
void stack<B>::push(B val)
{
    if(size == MAX_SIZE) //if full call error
    {
        throw overflow_error("Called push on full stack.");
    }
    else
    {
        for(int i = size - 1; i >= 0; --i) //push all of the values back one so index 0 can be changed
        {
            arr[i + 1] = arr[i];
        }
        arr[0] = val; //change index 0
        size = size + 1; //add one to the size
    }
    
}
template<typename C>
void stack<C>::pop()
{
    if(size == 0) //if empty call error
    {
        throw out_of_range("Called pop on empty stack.");
    }
    else
    {
        for(int i = 0; i < size; ++i) //push all of the values up by one thus removing the value that was first (gets overwritten)
        {
            arr[i] = arr[i + 1];
        }
        size = size - 1; //subtract one to the size 
    }
    
}
template<typename D>
D stack<D>::top()
{
    if(empty()) //if its empty call error
    {
        throw underflow_error("Called top on empty stack.");
    }
    else
    {
        return arr[0]; //return the first element
    }
};
template<typename E>
bool stack<E>::empty()
{   
    if(size == 0) //if the size is 0 then it is empty
    {
        return true;
    }
    return false;
}
#endif
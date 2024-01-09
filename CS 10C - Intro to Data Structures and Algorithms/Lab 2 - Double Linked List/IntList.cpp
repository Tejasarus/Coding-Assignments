#include "IntList.h"
#ifndef INTLIST_C
#define INTLIST_C
#include <iostream>
using namespace std;

IntList::IntList()
{
    dummyhead = new IntNode(0);
    dummytail = new IntNode(0);
    dummyhead->next = dummytail;
    dummytail->prev = dummyhead;
    
}
IntList::~IntList()
{
    while(!empty())
    {
        pop_front();
    }
}
void IntList::push_front(int value)
{
    IntNode* t = dummyhead->next; //copy the pointer after dummy head 
    dummyhead->next = new IntNode(value); //make the pointer after dummy head the new node
    dummyhead->next->next = t; //make the next pointer (now the second pointer) the old first pointer 
    dummyhead->next->next->prev = dummyhead->next; //set the previous pointer of the new second pointer to the new first pointer
    dummyhead->next->prev = dummyhead; //set the previous pointer of the new first node to the dummy head
}
void IntList::pop_front()
{
    if(dummyhead->next!=nullptr)//if the first value node is not nullptr
    {
        IntNode* temp = dummyhead->next;
        dummyhead->next = dummyhead->next->next;
        delete temp;
    }
}
bool IntList::empty() const
{
    if(dummyhead->next == dummytail)
    {
        return true;
    }
    return false;
}
void IntList::push_back(int value)
{
    IntNode* temp = new IntNode(value); //make a node w/ the value
    temp->next = dummytail; //point the node to the dummytail;
    temp->prev = dummytail->prev; //set the new last node prev to the previous last node which is still stored as dummytail prev 
    dummytail->prev = temp; //set dummy tail prev to the new node
    temp->prev->next = temp; //point the prev to the new node
}
void IntList::pop_back()
{
    if(dummytail->prev == dummyhead) //if empty
    {
        return;
    }
    else
    {
        dummytail->prev = dummytail->prev->prev; //set the dummy tail prev to the node before the one that will be removed
        delete dummytail->prev->next; //adios previous node
        dummytail->prev->next = dummytail; //point the prev to the dummytail
    }
}
ostream & operator<<(ostream &out, const IntList &rhs)
{
    IntNode* temp = rhs.dummyhead->next;
     while(temp != rhs.dummytail)
    {
        if(temp->next == rhs.dummytail)
        {
            out << temp->data;
        }
        else
        {
            out << temp->data << " ";
        }
        temp = temp->next;
    }
    return out;
    /*
    if(rhs.dummyhead!=0) //if the list isnt empty
    {
       IntNode* temp = rhs.dummyhead->next;
        while(temp->next != rhs.dummytail) 
       {
           out << temp->data << " ";
           temp = temp->next;
       }
       out << temp->data; //this is why you cant use a for loop, otherwise there would be a space at the end of the lst
      
    }
    return out;
    */
}
void IntList::printReverse() const
{
    //same as the out operator but backwards =)
    IntNode* temp = dummytail->prev;
     while(temp != dummyhead)
    {
        if(temp->next == dummyhead)
        {
            cout << temp->data;
        }
        else
        {
            cout << temp->data << " ";
        }
        temp = temp->prev;
    }
}
#endif
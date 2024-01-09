#include "IntList.h"
#ifndef INTLIST
#define INTLIST
#include <iostream>
using namespace std;

IntList::IntList()
{
    head = nullptr;
    tail = nullptr;
}
IntList::~IntList()
{
    while(!empty())
    {
        pop_front();
    }
}
void IntList::push_front(int num)
{
    IntNode* t = head;
    head = new IntNode(num);
    head->next = t;  
}
void IntList::pop_front()
{
    if(!empty())
    {
        IntNode* temp = head;
        head = head->next;
        delete temp;
        if(head == nullptr)
        {
            tail = nullptr;
        }
    }
    else
    {
        return;
    }
    
}
bool IntList::empty() const
{
    
    if(head == nullptr && tail == nullptr)
    {
        return true;
    }
    return false;
    
  
}
const int& IntList::front() const
{
   // IntNode* t = head;
   // int x = &t;
    //return x;
    if(empty())
    {
        exit(1);
    }
    else
    {
        return head->value;
    }
    
   // return ee;
}
const int& IntList::back() const
{
    if(empty())
    {
        return tail->value;
    }
    else
    {
        IntNode* temp = head;

        while(temp->next != 0)
        {
        temp = temp->next; 

        if(temp->next == 0)
        {
            return temp->value;
        }
        }

        if(temp->next == 0)
        {
            return temp->value;
        }
        else
        {
            return tail->value;
        }
    }

    
}
ostream& operator<<(ostream & out, const IntList & list)
{
   
    if(list.empty())
    {
        return out;
    }
    IntNode* temp = list.head;
    while(temp != nullptr)
    {
        if(temp->next == nullptr)
        {
            out << temp->value;
            temp = temp->next;
        }
        else
        {
            out << temp->value << " ";
            temp = temp->next;
        }
        
    }
    return out;
 
}
IntList::IntList(const IntList &cpy)
{
    head = nullptr;
    tail = nullptr;
    for(IntNode* t = cpy.head; t != nullptr; t = t->next)
    {
        push_back(t->value);
    }

}
IntList& IntList::operator=(const IntList &rhs)
{   
    if(this != &rhs)
    {
        clear();
    
    if(rhs.empty())
    {
        head = 0;
        tail = 0;
    }
    for(IntNode* t = rhs.head; t != nullptr; t = t->next)
    {
        push_back(t->value);
    }
    }
    return *this;
}
void IntList::push_back(int value)
{
    IntNode* t = new IntNode(value);
    if(head == nullptr)
    {
        head = t;
        tail = t;
    }
    else
    {
        IntNode* temp = head;
        while(temp != nullptr)
        {
            if(temp->next == nullptr)
            {
                temp->next = t;
                tail = t;
                break;
            }
            else
            {
                temp = temp->next;
            }
        }
    }
    
}
void IntList::clear()
{
    while(head != nullptr)
    {
        pop_front();
    }
    head = nullptr;
    tail = nullptr;
}
void IntList::selection_sort()
{
    IntNode* t = head;
    while(t != nullptr)
    {
        IntNode* m = t;
        IntNode* rep = t->next;

        while(rep != nullptr)
        {
            if(m->value > rep ->value)
            {
                m = rep;
            }
            rep = rep->next;
        }
        int temp = t->value;
        t->value = m->value;
        m->value = temp;
        
        tail = t;
        t = t->next;
    }
    
    
}
void IntList::insert_ordered(int value)
{
    IntNode* t = head;
    if(head == nullptr)
    {
        tail = head;
        push_back(value);
    }
    else if(head->value >= value)
    {
        tail = head;
        push_front(value);
    }
    else if(back() <= value)
    {
        push_back(value);
    }
    else
    {
        while(t != nullptr)
        {
            IntNode* nextval = t->next;
            if(t-> value < value && nextval->value > value)
            {
                IntNode* rep = new IntNode(value);
                rep->next = nextval;
                t->next = rep;
                break;
            }
            else if(t-> value == value)
            {
                IntNode* rep = new IntNode(value);
                rep->next = nextval;
                t->next = rep;
                break;
            }
            else
            {
                t = t->next;
            }
            
        }
    }
}
void IntList::remove_duplicates()
{
    IntNode* pot_copy = 0;
    IntNode* previous = head;
    for(IntNode* t = head; t != nullptr; t= t->next)
    {
        pot_copy = t->next; //DO THE PARALLEL POINTER THING
        previous = t;
        while(pot_copy!=nullptr)
        {
            if(pot_copy->value == t->value)
            {
               // cout << "match" << endl;
                IntNode* trash = pot_copy;
                
                    previous->next = pot_copy->next;
                    pot_copy = pot_copy->next;
                    delete trash;
                
                
            }
            else
            {
                pot_copy = pot_copy->next;
                previous = previous->next; //parallel!
            }
            
        }
    }
}
#endif
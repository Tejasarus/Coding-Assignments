#include "SortedSet.h"
#ifndef SORTEDSET
#define SORTEDSET

SortedSet::SortedSet()
{
    
}
SortedSet::SortedSet(const SortedSet &s)
{
    *this = s;
}
SortedSet::SortedSet(const IntList &l) : IntList(l)
{
    selection_sort();
    
}
SortedSet::~SortedSet()
{
    
}
bool SortedSet::in(int value)
{
    IntNode *t = head;
    while(t != nullptr)
    {
        if(t->value == value)
        {
            return true;
        }
        else
        {
            t = t->next;
        }
    }
    return false;
}
void SortedSet::add(int value)
{
    if(head == 0)
    {
        IntList::push_back(value);
    }
    else if(!in(value))
    {
        IntList::insert_ordered(value);
    }
}
void SortedSet::push_front(int value)
{
    add(value);
}
void SortedSet::push_back(int value)
{
    add(value);
}
void SortedSet::insert_ordered(int value)
{
    add(value);
}
SortedSet& SortedSet::operator|=(const SortedSet& set)
{
    IntNode* node1 = set.head;
    IntNode* node2 = head;
    if(node1 == nullptr)
    {
        return *this;
    }
    while(node1 != nullptr)
    {
        add(node1->value);
        node1 = node1 -> next;
    }
    while(node2 != nullptr)
    {
        add(node2->value);
        node2 = node2->next;
    }
    return *this;
}
SortedSet SortedSet::operator&(const SortedSet& set)
{
    SortedSet r;
    IntNode* x = set.head;
   // cout << "maybe" << endl;
    while(x != nullptr)
    {
       // cout << "yes" << endl;
        if(in(x->value))
        {
            r.push_back(x->value);
            x = x->next;
        }
        else
        {
            x = x->next;
        }
    }
    return r;
}
SortedSet SortedSet::operator|(const SortedSet& set)
{
    SortedSet t;
    t = *this;
   // cout << t << endl;
    IntNode* x = set.head;
    while(x != nullptr)
    {
        t.add(x->value);
        x = x->next;
    }
   // cout << t << endl;
    return t;
}
SortedSet SortedSet::operator&=(const SortedSet& set)
{
    SortedSet r;
    IntNode* x = set.head;
    while(x != nullptr)
    {
        if(in(x->value))
        {
            r.push_back(x->value);
            x = x->next;
        }
        else
        {
            x = x->next;
        }
    }
    *this = r;
    return r;
}
#endif
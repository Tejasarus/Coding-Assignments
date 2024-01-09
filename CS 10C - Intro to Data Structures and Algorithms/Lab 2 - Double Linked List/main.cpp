#include "IntList.h"
#include <iostream>
using namespace std;

int main()
{
    IntList t;
    t.push_front(5);
    if(t.empty())
    {
        cout << "yes" << endl;
    }
    else
    {
        cout << "no" << endl; //supposed to cout this one
    }
    t.pop_front();
    if(t.empty())
    {
        cout << "yes" << endl; //supposed to cout this one
    }
    else
    {
        cout << "no" << endl;
    }
    t.push_back(5);
    t.push_front(5);
    if(t.empty())
    {
        cout << "yes" << endl;
    }
    else
    {
        cout << "no" << endl; //supposed to cout this one
    }
    t.pop_back();
    if(t.empty())
    {
        cout << "yes" << endl; //supposed to cout this one
    }
    else
    {
        cout << "no" << endl;
    }
    t.push_front(5);
    t.push_back(12);
    t.push_front(30);
    cout << t << endl;
    t.printReverse();
    return 0;
}
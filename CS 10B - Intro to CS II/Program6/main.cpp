#include "IntList.h"
#include "SortedSet.h"
#include <iostream>
using namespace std;

int main() {
   
   SortedSet sorted;
  // sorted.push_front(-123);
   if(sorted.in(10))
   {
      cout << "yes" << endl;
   }
   else
   {
      cout << "no" << endl;
   }
   sorted.add(12);
   sorted.add(-99);
   cout << sorted << endl;

   SortedSet sorty;
   sorty.push_back(12);
   sorty.push_back(32);
   cout << "sorty is: " << sorty << endl;
   sorty = sorty |= sorted;
   cout << "sorty is now: " << sorty << endl;

   SortedSet x;
   SortedSet y;
   SortedSet z;
   SortedSet a;
   x.push_back(2);
   x.push_back(-312);
   x.push_back(74);
   y.push_back(74);
   y.push_back(-74);
   cout << "x is: " << x << endl;
   cout << "y is: " << y << endl;
   x &= y;
   cout << "x new is: " << x << endl;
   // a = x & y;


   // cout << "a is: " << a << endl;

   SortedSet s1;
   SortedSet s2;
   s1.push_back(0);
   s2 = s1;
   cout << "s2 is: " << s2 << endl;
   
   SortedSet sset(s1);
   cout << "set is: " << sset << endl;

   IntList list;
   IntList list2;
   list.push_back(110);
   list.push_back(20);
   list2 = list;
   cout << "list2 is: " << list2 << endl;
   cout << "listasd is " << list << endl;
   SortedSet sset2(list);
   //sset2.selection_sort();
   cout << "sset2 is: " << sset2 << endl;
   cout << "hi" << endl;

/*
  g++ main.cpp IntList.cpp SortedSet.cpp
     gdb ./a.exe core
   
   */
   return 0;
}

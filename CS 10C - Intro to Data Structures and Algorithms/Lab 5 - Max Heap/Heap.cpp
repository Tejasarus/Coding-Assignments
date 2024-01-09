#ifndef HEAP
#define HEAP
#include "Heap.h"
#include <iostream>
#include <array>
using namespace std;


Heap::Heap()
{
    numItems = 0; //the array has no items
}

void Heap::enqueue(PrintJob* job)
{
    //Insert PrintJob pointer at the next available position.
    if(numItems < MAX_HEAP_SIZE) {
        
        //Insert pointer in the case where the array is empty.
        if(numItems == 0) {
            arr[numItems] = job;
        }
        else {
            int x = numItems;
            
            //Consider the case where the new PrintJob could violate the heap property. Percolate the new pointer up.
            while(x > 0 && arr[(x-1)/2]->getPriority() < job->getPriority()) {
                arr[x] = arr[(x-1)/2];
                
                x = (x-1)/2;
            }
            
            arr[x] = job;
        }
        
        ++numItems;
    }
}

void Heap::dequeue()
{
    if(numItems == 0) //if heap is empty return
    {
        return;
    }
    else
    {
        PrintJob* last;
        for(int i = 0; i < numItems; ++i) //get the last element in the array
        {
            last = arr[i];
        }
        arr[0] = last; // make the root the last node
        trickleDown(0); //heapify
        --numItems; //decrease the list by 1;
    }
    
    
}
PrintJob* Heap::highest()
{
    if(numItems == 0) //if heap is empty return
    {
        return nullptr;
    }
    return arr[0];
}
void Heap::print()
{
    if(numItems == 0) //if heap is empty return
    {
        return;
    }
     cout << "Priority: " << arr[0]->getPriority()
         << ", Job Number: " << arr[0]->getJobNumber()
         << ", Number of Pages: " << arr[0]->getPages() << endl;
}

void Heap::trickleDown(int num)
{
    int largest = num; 
    int l = 2 * num + 1; // left 
    int r = 2 * num + 2; // right 
  
    //if left is larger
    if (l < numItems && arr[l]->getPriority() > arr[largest]->getPriority()) 
    {
        largest = l;
    }

    //if right child is larger    
    if (r < numItems && arr[r]->getPriority() > arr[largest]->getPriority()) 
    {
        largest = r;
    }
    
    //if the largest was changed, swap
    if (largest != num) 
    {
        swap(arr[num], arr[largest]);
        trickleDown(largest);
    }
}
#endif
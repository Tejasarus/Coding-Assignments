#include <iostream>
#include <time.h>
using namespace std;
int midpt(int numbers[], int i, int k)
{
    
    int midpoint,pivot,l,h,temp;
    bool isdone = false;
    midpoint = i + (k - i) / 2; //get the middle as the pivot
    pivot = numbers[midpoint];

    /* Initialize variables */
    l = i;
    h = k;

    while (!isdone) {
        /* Increment l while numbers[l] < pivot */
        while (numbers[l] < pivot) 
        {
            ++l;
        }

        /* Decrement h while pivot < numbers[h] */
        while (pivot < numbers[h]) 
        {
            --h;
        }
        /* If there are zero or one items remaining,
        all numbers are partitioned. Return h */
        if (l >= h) //if the amount of low #s are = or greater than (odd #s) the high, you're done
        {
            isdone = true;
        }
        else {
            /* Swap numbers[l] and numbers[h],
                update l and h */
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;

            ++l;
            --h;
        }
    }
    return h;
}

void Quicksort_midpoint(int numbers[], int i, int k)
{
    /*
    this function sorts the given array 
    in the range from i to k using quicksort method. 
    In this function, pivot is the midpoint element (numbers[(i+k)/2]).
    */
    if( i >= k)
    {
        return;
    }
    int index = midpt(numbers, i, k);

    Quicksort_midpoint(numbers, i, index); //sort left

    Quicksort_midpoint(numbers, index + 1, k); //sort right
}
int medoftree(int numbers[], int i, int k)
{
    int l,h,midpt,med,temp,pivot;
    bool done = false;
    midpt = i + (k - i) / 2; //pivot is the midpoint element (numbers[(i+k)/2])
    
    //now we find the median "middle of the three values"
    if ((numbers[midpt] >= numbers[i] && numbers[midpt] <= numbers[k]) || (numbers[midpt] >= numbers[k] && numbers[midpt] <= numbers[i])) 
    { //if midpt is greater than first index and less than last index,
        med = midpt;
    }
    else if ((numbers[i] <= numbers[midpt] && numbers[i] >= numbers[k]) || (numbers[i] >= numbers[midpt] && numbers[i] <= numbers[k])) 
    { //if first index is in between the other two
        med = i;
    }
    else if ((numbers[k] <= numbers[i] && numbers[k] >= numbers[midpt]) || (numbers[k] >= numbers[i] && numbers[k] <= numbers[midpt])) 
    {//if last index is in between the other two
        med = k; 
    }

    pivot = numbers[med]; //make the pivot the median 
    l = i;
    h = k;
    
    while (!done) {
        while (numbers[l] < pivot) {
            ++l;
        }
        while (pivot < numbers[h]) {
            --h;
        }
        if (l >= h) {
            done = true;
        }
        else {
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;
            
            ++l;
            --h;
        }
    }
    
    return h;
}
void Quicksort_medianOfThree(int numbers[], int i, int k)
{
    /*
    his function utilizes different pivot selection technique in quicksort 
    algorithm. The pivot is the median of the following three values: leftmost 
    (numbers[i]), midpoint (numbers[(i+k)/2]) and rightmost (numbers[k])
    */
    if(i >= k) //if there are two (or one) elements and they are sorted, return
    {
       return;
    }

    int index = medoftree(numbers, i, k); //get median

    Quicksort_medianOfThree(numbers,i,index); //sort left side

    Quicksort_medianOfThree(numbers, index +1, k); //sort right side
}
void InsertionSort(int numbers[], int numbersSize)
{
    /*
    this function sorts the given array using InsertionSort method.
    */
    int i;
    int j;
    int temp;      
   
    for (i = 1; i < numbersSize; ++i) //cycle through the list
    {
      j = i;

      while (j > 0 && numbers[j] < numbers[j - 1]) 
      //If the current element is less than the element to the left, swap the values 
      { 
        temp = numbers[j];
        numbers[j] = numbers[j - 1];
        numbers[j - 1] = temp;
        --j;
      }
   }
}
///////////////////////////////////////////////////////////////////
const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}
void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}
/////////////////////////////////////////////////////////////////////
int main()
{
    //make the three arrays and fill them with random ints
    int arr1[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];
    fillArrays(arr1,arr2,arr3);

    const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds
    
    //print the unsorted arrays
    /*
    for(int i = 0; i < NUMBERS_SIZE; ++i)
    {
        cout << arr1[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < NUMBERS_SIZE; ++i)
    {
        cout << arr2[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < NUMBERS_SIZE; ++i)
    {
        cout << arr3[i] << " ";
    }
    cout << endl;
    cout << endl;
    */
    //sort the arrays
    clock_t Start = clock();
    Quicksort_midpoint(arr1,0,NUMBERS_SIZE - 1);
    clock_t End = clock();
    int elapsedTime = (End - Start);//CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
     cout << "midpoint" << elapsedTime << endl;
     Start = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE-1);
     End = clock();
     elapsedTime = (End - Start);//CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
     cout << "median of three" << elapsedTime << endl;
     Start = clock();
    InsertionSort(arr3,NUMBERS_SIZE);
     End = clock();
     elapsedTime = (End - Start);//CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "insertion" << elapsedTime << endl;
    //print the sorted arrays
    /*
    for(int i = 0; i < NUMBERS_SIZE; ++i)
    {
        cout << arr1[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < NUMBERS_SIZE; ++i)
    {
        cout << arr2[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < NUMBERS_SIZE; ++i)
    {
        cout << arr3[i] << " ";
    }
    */
   // cout << elapsedTime;
    
    return 0;
}
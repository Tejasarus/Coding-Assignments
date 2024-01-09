#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <time.h>
using namespace std;


template<typename A>
A getElement(vector<A> vals, int index)
{
    return vals.at(index); //just has to return element at the index
}

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

template<typename S> //sets the template name to "S" 
unsigned min_index(const vector<S> &vals, unsigned index)
{
    int size = vals.size();
    S min = vals.at(index);
    for(int i = index; i < size; ++i) //cycle through the list starting from index
    {
        if(vals.at(i) < min) //if the val at i is less than the min
        {
            min = vals.at(i); //make the min that value
            index = i; //set the index to the i so we can return it
        }
    }
    return index;
}

template<typename T> //sets the template name to "T" 
void selection_sort(vector<T> &vals)
{   
    int size = vals.size();
    int num;
    T temp;
    for(int i = 0; i < size - 1; ++i)
    {
        num = min_index(vals, i);
        temp = vals.at(num);//get the min #

        if(num != i)//swap the two in the vector
        {
           vals.at(num) = vals.at(i);
           vals.at(i) = temp;
        }
    }
   
}

int main()
{
    vector<int> numbers = {-10,14,16,12,9,-9,5,-6,17,-8,-19,-1};
    vector<string> words = {"hi", "bye", "cya","a","bb"};
    int num;
    num = min_index(numbers, 0);
    cout << "num is: " << num << endl;
    num = min_index(words, 0);
    cout << "num is: " << num << endl;
    selection_sort(numbers);
    selection_sort(words);
    int nsize = numbers.size();
    int wsize = words.size();
    for(int i = 0; i <nsize; ++i)
    {
        cout << numbers.at(i) << endl;
    }
    for(int i = 0; i < wsize; ++i)
    {
        cout << words.at(i) << endl;
    }


    //Part B
    
     srand(time(0));
     vector<char> vals = createVector();
     char curChar;
     int index;
     int numOfRuns = 10;
     try{//try block
        while(--numOfRuns >= 0){
                cout << "Enter a number: " << endl;
                cin >> index;
                int s = vals.size();
                if(index > s-1)
                {
                     throw runtime_error("out of range exception occured");
                }

                curChar = getElement(vals,index);
                cout << "Element located at " << index << ": is " << curChar << endl;
            }
     }
    catch(runtime_error& excpt)//catch the error if there is one
    {
        cout << excpt.what() << endl;
        //cout << "out of range exception occured" << endl;
    }
    
    return 0;
}
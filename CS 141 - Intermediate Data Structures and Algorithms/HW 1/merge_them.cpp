#include <iostream>
#include <vector>
using namespace std;

// #of candies to sudent, difference between their score and the highest score in the merge.
// if two students have the same low score, only give candy to one of them 

int candies = 0;
//int temp_scores[2];
void print(vector<int>a)
{
    cout << "vector: ";
    for(int i = 0; i < a.size(); ++i)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int get_highest(vector<int> v)
{
    int high = -1;
    for(int i = 0; i < v.size(); ++i)
    {
        if(high < v[i])
        {
            high = v[i];
        }
    }
    return high;
}

int get_lowest(vector<int> v)
{
    int low = 10000;
    for(int i = 0; i < v.size(); ++i)
    {
        if(low > v[i])
        {
            low = v[i];
        }
    }
    return low;
}

bool find(vector<int> v, int n)
{
    for(int i = 0; i < v.size(); ++i)
    {
        if(v[i] == n)
        {return true;}
    }
    return false;
}

void Merge(vector<int>& scores, int beg, int mid, int end)
{
    vector<int> temp;
    int left = beg, right = mid + 1;
    int highest = -1, lowest = 10000;

    while(left <= mid && right <= end)
    {
        //cout << "nums: " << endl << scores[left] << endl;
        //cout << scores[right] << endl;
        
        if(scores[left] <= scores[right])
        {
            temp.push_back(scores[left]);
            ++left;
        }
        else
        {
            temp.push_back(scores[right]);         
            ++right;
        }
    }

    while(left <= mid)
    {
        temp.push_back(scores[left]);
        ++left;
    }
    while(right <= end)
    {
        temp.push_back(scores[right]);
        ++right;
    }
    //print(temp);
    //cout << "high " << get_highest(temp) << endl;
    //cout << "low " << get_lowest(temp) << endl;
    candies = candies + (get_highest(temp) - get_lowest(temp));
    for(int i = beg; i <= end; ++i)
    {
        scores[i] = temp[i - beg];
    }
}

void MergeSort(vector<int>& scores, int beginning, int end)
{
   if(beginning < end)
   {
    int middle = (beginning + end)/2;
    MergeSort(scores,beginning,middle);
    MergeSort(scores,middle+1,end);
    Merge(scores,beginning,middle,end);
   }
}

int main()
{
    ios_base::sync_with_stdio(false);
    int size, value;
    cin >> size;
    vector<int> scores;
    for(int i = 0; i < size; ++i)
    {
        cin >> value;
        scores.push_back(value);
    }
    
    MergeSort(scores, 0, size - 1);
    cout << candies << endl;

   // print(scores);
    return 0;
}
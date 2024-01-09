#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    float departments;
    cin >> departments;
    int votes_needed = (int)((departments/2)+0.5f);
    //cout << "votes " << votes_needed << endl;

    vector<float> v;
    int val;
    for(int i = 0; i < departments; ++i)
    {
        cin >> val;
        v.push_back(val);
    }

    sort(v.begin(),v.end());

    int convince = 0;

    for(int i = 0; i < votes_needed; ++i)
    {
        convince = convince + ((int)((v[i]/2)+0.5f));
    }
    cout << convince << endl;
}
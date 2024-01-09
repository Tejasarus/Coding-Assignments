#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int time, upper, lower, score = 0, a, b, c;
    cin >> time >> upper >> lower;
    vector<int> scoring;
    for(int i = 0; i < time; ++i)
    {
        scoring.push_back(0);
    }

    for(int i = 0; i < upper + lower; ++i)
    {
        cin >> a >> b >> c;
        int counter = a;
        for(int i = 0; i <= b-a; ++i)
        {
            //cout << "counter: " << counter << endl;
            if(c == 1)
            {
                scoring[counter] = 3;
            }
            else
            {
                if(scoring[counter]!=3)
                {
                    scoring[counter] = 1;
                }
                
            }
            ++counter;
        }
    }
    for(int i = 0; i < time; ++i)
    {
        //cout << i << ": " << scoring[i] << endl;
        score = score + scoring[i];
    }
    
    /*
    int a,b,c,score = 0;
    for(int i = 0; i < upper; ++i)
    {
        cin >> a >> b >> c;
        int temp = b - a;
        if(c = 1)
        {
            temp = temp * 3;
            
        }
        score = score + temp;
    }
    for(int i = 0; i < lower; ++i)
    {
        cin >> a >> b >> c;
        int temp = b - a;
        if(c = 1)
        {
            temp = temp * 3;
            
        }
        score = score + temp;
    }

    */
    cout << score << endl;
    return 0;
};
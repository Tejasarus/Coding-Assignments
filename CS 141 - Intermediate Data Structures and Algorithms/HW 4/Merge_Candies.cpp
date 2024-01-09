#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print(vector<int>a)
{
    cout << "vector: ";
    for(int i = 0; i < a.size(); ++i)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main()
{
    int lines,input, result = 0;
    vector<int> bags,results;
    cin >> lines;
    for(int i = 0; i < lines; ++i)
    {
        cin >> input;
        bags.push_back(input);
    }

    sort(bags.begin(), bags.end());
    //print(bags);
    vector<int> temp;
    
    for(int i = 0; i < lines; ++i)
    {

        if(i + 1 != lines)
        {
            result = result + ((bags[i] + bags[i+1])*2);
            bags[i+1] = bags[i] + bags[i+1];
            //print(bags);
            //bags.erase(bags.begin());
            sort(bags.begin(), bags.end());
            //print(bags);
        }
    }

    /*
    print(results);
    for(int i = 0; i < results.size(); ++i)
    {
        result = result + (results[i]);
    }
    */
    cout << result<< endl;

    return 0;
}
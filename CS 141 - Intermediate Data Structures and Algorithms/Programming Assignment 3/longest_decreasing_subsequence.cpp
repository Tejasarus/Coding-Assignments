#include <iostream>
#include <vector>
using namespace std;

int max(int a, int b)
{
    if(a > b)
    {
        return a;
    }
    return b;
}

int lcs(vector<int> v, int size)
{
    vector<int> list;
    for(int i = 0; i < size; ++i)
    {
        list.push_back(1);
    }

    for(int i = 1; i < size; ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            if(v[i] < v[j] && list[i] < list[j] + 1)
            {
                list[i] = list[j] + 1;
            }
        }
    }

    int res = 0;
    for(int i = 1; i < size; ++i)
    {
        res = max(res,list[i]);
    }

    return res;
}

int main()
{
    vector<int> list;
    int size, input, result;
    cin >> size;

    for(int i = 0; i < size; ++i)
    {
        cin >> input;
        list.push_back(input);
    }

    result = lcs(list, size);
    cout << result << endl;

    return 0;
}
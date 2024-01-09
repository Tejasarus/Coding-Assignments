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
int max(int a, int b)
{
    //cout << "int a: " << a << " int b: " << b << endl;
    if(a > b){//cout << "max: " << a << endl;
    return a;}
   // cout << "max: " << b << endl;
    return b;
}
int knapsack(vector<int> weight, vector<int> value, int budget, int n)
{
    //k is n and n is budget
    vector<int> result;
    for(int t = 0; t < budget + 1; ++t)
    {
        result.push_back(0);
    }

    for(int i = 0; i < n; ++i)
    {
        for(int j = budget; j >= 0; --j)
        {
            if(j - weight[i] >=0)
            {
                result[j] = max(result[j], result[j-weight[i]]+value[i]);
            }
        }
    }
    return result[budget];
}

int main()
{
    int budget, lines, num1, num2;
    vector<int> weight, value;
    cin >> budget >> lines;
    for(int i =0; i < lines; ++i)
    {
        cin >> num1 >> num2;
        weight.push_back(num1);
        value.push_back(num2);
    }
    //print(weight);
    //print(value);
    int result = knapsack(weight, value, budget, lines);

    cout << result << endl;
    return 0;
}
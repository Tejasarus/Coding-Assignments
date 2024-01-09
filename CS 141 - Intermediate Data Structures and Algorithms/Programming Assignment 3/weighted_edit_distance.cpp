#include <iostream>
#include <vector>
using namespace std;


int minium_val(int a, int b, int c)
{
    return min(min(a,b),c);
}

int sum(vector<int> list, int size)
{
    int sum = 0;
    for(int i = 0; i < size; ++i)
    {
        sum += list[i];
    }
    return sum;
}

void print(vector<vector<int>> dp, int size1, int size2)
{
    cout << "table:" << endl;
    for(int i = 1; i <= size1; ++i)
    {
        for(int j = 1; j <= size2; ++j)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

int distance(vector<int> list1, vector<int> list2, int size1, int size2)
{
        vector<vector<int>> dp(size1 +1, vector<int>(size2 +1, 0));
       

        for(int i = 1; i <= size1; ++i)
        {
            dp[i][0] = sum(list1,i);
        }
            
        for(int j = 1; j <=size2; ++j)
        {
            dp[0][j] = sum(list2,j);
        }

        //print(dp,size1,size2);

        for(int i = 1; i <= size1; i++)
        {
            for(int j = 1; j <=size2; j++)
            {
                if(list1[i-1] == list2[j-1])
                {
                    dp[i][j] = dp[i-1][j-1];
                }
                else
                {
                    int insert = list1[i-1];
                    int remove = list2[j-1];
                    int replace = abs(list1[i-1] - list2[j-1]);

                    dp[i][j] = minium_val(dp[i-1][j] + insert, dp[i][j-1] + remove, dp[i-1][j-1] + replace);
                    
                }
            }
        }
        
        return dp[size1][size2];
    //works but is too slow
    /*
    if(size1 == 0)
    {
        return sum(list2,size2);
    }
    if(size2 == 0)
    {
        return sum(list1,size1);
    }
    if(list1[size1] == list2[size2])
    {
        distance(list1, list2, size1-1, size2-1);
    }


    int insert = list1[size1-1];
    int remove = list2[size2-1];
    int replace = abs(list1[size1-1] - list2[size2-1]);

    return minium_val(distance(list1, list2,size1-1,size2)+insert,distance(list1, list2,size1,size2-1)+remove,distance(list1,list2,size1-1,size2-1)+replace);
    */
}


int main()
{
    int size1, size2;
    cin >> size1 >> size2;

    vector<int> list1, list2;
    int input;
    for(int i = 0; i < size1; ++i)
    {
        cin >> input;
        list1.push_back(input);
    }
    for(int i = 0; i < size2; ++i)
    {
        cin >> input;
        list2.push_back(input);
    }
    int result = distance(list1,list2,size1,size2);
 
    cout << result << endl; 
    return 0;
}
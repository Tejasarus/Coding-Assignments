#include <iostream>
#include <vector>
using namespace std;

void prims(vector<vector<int>>, int size)
{

}

int main()
{

    int m, n, s, t;
    cin >> n >> m;
    cin >> s >> t;

    vector<vector<int>> dp(n, vector<int>(n, 0));

    int x, y, z;

    for(int i = 0; i < m; ++i)
    {
        cin >> x >> y >> z;
        dp[x][y] = z;   
    }

    prims(dp);
	return 0;
}
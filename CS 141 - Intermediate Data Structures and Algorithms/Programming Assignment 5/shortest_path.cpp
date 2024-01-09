#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#define INT_MAX 2147483647
using namespace std;

/*
int min_dist(vector<int> distance, vector<bool> smallest)
{
    int min = 10000;
    int index;
    for(int i = 0; i < distance.size(); ++i)
    {
        if(smallest[i] == false && distance[i] < min)
        {
            min = distance[i];
            index = i;
        }
    }
    return index;
}


void dijkstra(vector<vector<int>> v, int start, int end, int size)
{
    vector<int> distance;
    vector<bool> shortest;

    int max = INT_MAX;
    for(int i = 0; i < size; ++i)
    {
        distance.push_back(max);
        shortest.push_back(false);
    }

    distance[start] = 0;

    for(int i = 0; i < size - 1; ++i)
    {
        int small = min_dist(distance,shortest);
        shortest[small] = true;

        for(int j = 0; j < size; ++j)
        {
            if(shortest[j] == false && v[small][j] && distance[small] != max && distance[small] + v[small][j] < distance[j])
            {
                distance[j] = distance[small] + v[small][j];
            }
        }
    }

    cout << distance[end] << endl;

}



void print(vector<vector<int>> dp, int size)
{
    cout << "table:" << endl;
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}
*/


struct Edge 
{
   int src, dest, weight;
};

struct Graph 
{
   int V, E;
   struct Edge* edge;
};

struct Graph* createGraph(int V, int E) 
{
   struct Graph* graph = new Graph;
   graph->V = V;
   graph->E = E;
   graph->edge = new Edge[E];
   return graph;
}

void bf(struct Graph* graph, int src, int end)
{
    int V = graph->V;
    int E = graph->E;
    int distance[V];

    for(int i = 0; i < V; ++i)
    {
        distance[i] = INT_MAX;
    }

    distance[src] = 0;

    for(int i = 1; i < V-1; ++i)
    {
        for(int j = 0; j < E; ++j)
        {
            int s = graph->edge[j].src;
            int t = graph->edge[j].dest;
            int w = graph->edge[j].weight;
            if(distance[s] != INT_MAX && distance[s] + w < distance[t])
            {
                distance[t] = distance[s] + w;
                if(t == end)
                {
                    break;
                }
            }
        }
    }

    cout << distance[end] << endl;
}

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, s, t, x, y, z;
    cin >> n >> m;
    cin >> s >> t;

    struct Graph* graph = createGraph(n,m);

    for(int i = 0; i < m; ++i)
    {
        cin >> x >> y >> z;
        graph->edge[i].src = x;
        graph->edge[i].dest = y;
        graph->edge[i].weight = z;
    }

    bf(graph,s,t);
/*
    vector<vector<int>> dp(n, vector<int>(n, 0));

   // int x, y, z;
    for(int i = 0; i < m; ++i)
    {
        cin >> x >> y >> z;
        dp[x][y] = z;   
    }

    dijkstra(dp,s,t,n);
*/
	return 0;
}
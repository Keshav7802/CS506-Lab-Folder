#include<bits/stdc++.h>
#include <cstdlib>
#define INF 999999
using namespace std;

bool BellmanFord(int V, vector<pair<int,int>> adj[])
{
    vector<int> dist(V + 1, INT32_MAX);
    dist[V] = 0;

    for (int i = 0; i < V; i++)
    {
        for (int u = V; u >= 0; u--)
        {
            for (auto x : adj[u])
            {
                int v = x.first;
                int wt = x.second;

                if (dist[u] != INT32_MAX && dist[u] + wt < dist[v])
                    dist[v] = dist[u] + wt;
            }
        }
    }

    for (int u = V; u >= 0; u--)
    {
        for (auto x : adj[u])
        {
            int v = x.first;
            int wt = x.second;

            if (dist[u] != INT32_MAX && dist[u] + wt < dist[v])
            {
                return true;
            }
        }
    }
    return false;
}

int main(){
    while(true){
        int n = 5;
        vector<pair<int, int>> *adj = new vector<pair<int,int>> [n+1];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int x = rand() % 10;
                int y = rand() % 2;
                int arr[] = {-1, 1};
                x *= arr[y];
                if (i != j)
                    adj[i].push_back({j, x});
            }
        }
        cout << n << endl;
        cout << BellmanFord(n, adj) << endl;
        if (!BellmanFord(n, adj)){
            vector<vector<int>> ans(n, vector<int>(n));
            for (int i = 0; i < n; i++)
            {
                for (auto j : adj[i])
                {
                    ans[i][j.first] = j.second;
                }
            }
            cout << n << " " << 1 << endl;
            for (auto i : ans)
            {
                for (auto j : i)
                    cout << j << " ";
                cout << endl;
            }
            break;
        }
    }
    return 0;
}
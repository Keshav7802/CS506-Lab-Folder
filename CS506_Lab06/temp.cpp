#include <bits/stdc++.h>
#include <time.h>
#define INF 999999
using namespace std;

vector<int> BellmanFord(int V, vector<pair<int, int>> adj[])
{
    vector<int> dist(V + 1, INF);
    vector<int> par(V + 1, -1);
    dist[V] = 0;
    int x;

    for (int i = 0; i < V; i++)
    {
        x = -1;
        for (int u = V; u >= 0; u--)
        {
            for (auto j : adj[u])
            {
                int v = j.first;
                int wt = j.second;

                if (dist[u] != INF && dist[u] + wt < dist[v]){
                    dist[v] = dist[u] + wt;
                    par[v] = u;
                    x = v;
                }
            }
        }
    }

    if(x != -1)
    {
        for (int i = 0; i < V; ++i)
            x = par[x];

        vector<int> cycle;
        for (int v = x;; v = par[v])
        {
            if (v == x && cycle.size() > 1)
                break;
            cycle.push_back(v);
        }
        reverse(cycle.begin(), cycle.end());

        for(auto i: cycle){
            dist[i] = INF;
        }
    }
    return dist;
}

vector<vector<int>> Dijkstra(int V, vector<pair<int, int>> adj[], set<int> cycle)
{
    vector<vector<int>> dist(V, vector<int>(V, INF));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

    for (int i = 0; i < V; i++)
    {
        int src = i;
        if(cycle.find(src) != cycle.end()){
            continue;
        }
        dist[i][i] = 0;
        q.push({0, src});

        while (!q.empty())
        {
            int node = q.top().second;
            int currDist = q.top().first;
            q.pop();
            if (dist[i][node] < currDist)
                continue;
            for (auto x : adj[node])
            {
                int ver = x.first;
                int wt = x.second;
                if (cycle.find(ver) == cycle.end() && wt + dist[i][node] < dist[i][ver])
                {
                    dist[i][ver] = wt + dist[i][node];
                    q.push({dist[i][ver], ver});
                }
            }
        }
    }
    return dist;
}

void Johnson(int V, vector<pair<int, int>> adj[])
{

    for (int i = 0; i < V; i++)
    {
        adj[V].push_back({i, 0});
    }

    vector<int> h = BellmanFord(V, adj);

    h.pop_back();
    adj[V].clear();

    for (int u = 0; u < V; u++)
    {
        for (int v = 0; v < adj[u].size(); v++)
        {   
            if(h[u] == INF || h[adj[u][v].first] == INF)
                continue;
            adj[u][v].second = adj[u][v].second + h[u] - h[adj[u][v].first];
        }
    }

    set<int> cycle;
    for (int i = 0; i < V;i++){
        if(h[i] == INF)
            cycle.insert(i);
    }

    vector<vector<int>> SP = Dijkstra(V, adj, cycle);

    for (int u = 0; u < V; u++)
    {
        for (int v = 0; v < V; v++)
        {
            if(SP[u][v] == INF)
                continue;
            SP[u][v] = SP[u][v] + h[v] - h[u];
        }
    }

    for (int u = 0; u < V; u++)
    {
        if(cycle.find(u) != cycle.end()){
            cout << -1 << endl;
            continue;
        }
        for (int v = 0; v < V; v++)
        {
            cout << SP[u][v] << " ";
        }
        cout << endl;
    }
}


int main()
{
    int T;
    cin >> T;
    vector<double> time_taken;
    while (T--)
    {
        clock_t start, end;
        double time;
        start = clock();
        int N, D;
        cin >> N >> D;
        vector<pair<int, int>> *adj = new vector<pair<int, int>>[N + 1];
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int dis;
                cin >> dis;
                if (dis != INF)
                    adj[i].push_back({j, dis});
            }
        }
        Johnson(N, adj);
        end = clock();
        time = (double)(end - start) / 1000;
        time_taken.push_back(time);
    }
    for (auto i : time_taken)
        cout << i << " ";
    cout << endl;
}
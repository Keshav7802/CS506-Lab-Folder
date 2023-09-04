#include<bits/stdc++.h>
#include <time.h>
#define INF 999999
using namespace std;

vector<int> BellmanFord(vector<vector<pair<int, int>>> &adj, int N)
{
    vector<int> dist(N + 1, INF);
    dist[0] = 0;

    for (int i = 0; i < N; i++)
    {
        for (int u = N; u >= 0; u--)
        {
            for (auto x : adj[u])
            {
                int v = x.first;
                int wt = x.second;

                if (dist[u] != INF && dist[u] + wt < dist[v])
                    dist[v] = dist[u] + wt;
            }
        }
    }

    for (int u = N; u >= 0; u--)
    {
        for (auto x : adj[u])
        {
            int v = x.first;
            int wt = x.second;

            if (dist[u] != INF && dist[u] + wt < dist[v])
            {
                cout << "Negative Cycle";
                exit(1);
            }
        }
    }
    return dist;
}

vector<vector<int>> Dijkstra(vector<vector<pair<int, int>>> &adj, int N)
{
    vector<vector<int>> dist(N, vector<int>(N, INF));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

    for (int i = 0; i < N; i++)
    {
        int src = i;
        dist[i][i] = 0;
        q.push({0, i});

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
                if (wt + dist[i][node] < dist[i][ver])
                {
                    dist[i][ver] = wt + dist[i][node];
                    q.push({dist[i][ver], ver});
                }
            }
        }
    }
    return dist;
}

vector<vector<int>> Johnsons_APSP(vector<vector<pair<int,int>>> &adj, int N){
    for (int i = 0; i < N; i++)
    {
        adj[0].push_back({i, 0});
    }
    vector<int> h = BellmanFord(adj, N);
    for (int i = 0; i < N;i++){
        h[i] = h[i + 1];
    }
    h.pop_back();
    adj[0].clear();

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < adj[i].size(); j++)
        {

            adj[i][j].second += h[i] - h[adj[i][j].first];
        }
    }

    vector<vector<int>> ans = Dijkstra(adj, N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            ans[i][j] += h[j] - h[i];
        }
    }
    return ans;
}

int main(){
    int T;
    cin >> T;
    vector<double> time_taken;
    while(T--){
        clock_t start, end;
        double time;
        start = clock();
        int N, D;
        cin >> N >> D;
        vector<vector<pair<int,int>>> adj(N + 1);
        for (int i = 1; i <= N;i++){
            for (int j = 1; j <= N;j++){
                int dis;
                cin >> dis;
                if(dis != INF) adj[i].push_back({j, dis});
            }
        }
        vector<vector<int>> ans = Johnsons_APSP(adj, N);
        for(auto i: ans){
            for(auto j: i)
                cout << j << " ";
            cout << endl;
        }
        end = clock();
        time = (double) (end - start) / 1000;
        time_taken.push_back(time);
    }
    for(auto i: time_taken)
        cout << i << " ";
    cout << endl;
}
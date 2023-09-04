/*
Here I used the VS Code Extension Code Runner Extension to get the ouput of following program
in the terminal and beside this I also run this program using
these commands
gcc A04_Keshav_2020EEB1177_22MCS506.cpp -lstdc++ -o A04_Keshav_2020EEB1177_22MCS506
cmd /c 'A04_Keshav_2020EEB1177_22MCS506 < input.txt > output.txt'
where A04_Keshav_2020EEB1177_22MCS506 is the exe file input.txt is the file containing input and output.txt where we want output
*/

#include <bits/stdc++.h>
using namespace std;

bool isValid(int nx, int ny, int N){
    if(nx >=0 && ny >= 0 && nx < N && ny < N)
        return true;
    return false;
}

bool sortbysec(pair<int, int> &p1, pair<int, int> &p2){
    if(p1.second >= p2.second)
        return true;
    return false;
}

void dfs(vector<vector<int>> &graph, vector<bool> &visit, vector<pair<int,int>> &time, int node, int &val){
    time[node].first = val++;
    visit[node] = true;
    for(auto i: graph[node]){
        if(!visit[i])
            dfs(graph, visit, time, i, val);
    }
    time[node].second = val++;
}

void TopoSort(vector<vector<int>> &graph, int N){
    vector<pair<int, int>> time(N);
    vector<bool> visit(N);
    int val = 1;
    for (int i = 0; i < N;i++){
        if(!visit[i])
            dfs(graph, visit, time, i, val);
    }
    map<int, int> m;
    for (int i = 0; i < N;i++){
        m[time[i].second] = i;
    }
    vector<int> ans;
    for (auto i: m){
        ans.push_back(i.second);
    }
    reverse(ans.begin(), ans.end());
    for (auto i : ans)
        cout << (i+1) << " ";
    cout << endl;
}

int find(vector<int> &indeg, int N){
    for (int i = 0; i < N;i++){
        if(indeg[i] == 0)
            return i;
    }
    return -1;
}

void Lexsmall_Toposort(vector<vector<int>> &graph, int N){
    vector<int> indeg(N, 0);
    for (int i = 0; i < N; i++)
    {
        for(auto j: graph[i])
            indeg[j]++;
    }
    set<int> zeroindeg;
    for (int i = 0; i < N;i++){
        if(indeg[i] == 0)
            zeroindeg.insert(i);
    }
    vector<int> ans(N);
    for (int i = 0; i < N;i++){
        if(zeroindeg.empty()){
            cout << -1 << endl;
            return;
        }
        int a = *zeroindeg.begin();
        zeroindeg.erase(zeroindeg.begin());
        indeg[a] = -1;
        ans[i] = a + 1;
        for(auto j: graph[a]){
            indeg[j]--;
            if(indeg[j] == 0)
                zeroindeg.insert(j);
        }
    }
    for(auto i: ans)
        cout << i << " ";
    cout << endl;
}

void Print(set<pair<double, vector<int>>> q){
    for(auto i: q){
        cout << i.first << " " << i.second[0] << " " << i.second[1] << endl;
    }
    cout << endl;
}

double Dijkstra(vector<vector<int>> &graph, int N, int par, int sx, int sy, int ex, int ey)
{
    vector<vector<double>> visit(N, vector<double>(N,-1));
    set<pair<double, vector<int>>> q;
    q.insert({0, {sx, sy}});
    visit[sx][sy] = true;
    while(!q.empty()){
        // Print(q);
        pair<double, vector<int>> p = *q.begin();
        q.erase(q.begin());
        vector<int> dx = {0, 1, 0, -1, 1, -1, 1, -1};
        vector<int> dy = {1, 0, -1, 0, 1, 1, -1, -1};
        if(par%2 == 1 || par == 0 || par > 8)
            return -1;
        for (int i = 0; i < par;i++){
            int nx = p.second[0] + dx[i];
            int ny = p.second[1] + dy[i];
            int dis = abs(dx[i]) + abs(dy[i]);
            if(isValid(nx, ny, N)){
                double cost = abs((double) graph[nx][ny] - (double) graph[p.second[0]][p.second[1]]);
                if(dis == 2)
                    cost = (double) cost * 1.5;
                double fcost = p.first + cost;
                if(visit[nx][ny] == -1){
                    q.insert({fcost, {nx, ny}});
                    visit[nx][ny] = fcost;
                }
                else if(fcost < visit[nx][ny]){
                    q.insert({fcost, {nx, ny}});
                    visit[nx][ny] = fcost;
                }
            }
        }
    }
    return visit[ex][ey];
}

int BFS(vector<vector<int>> &graph, int N, int par, int sx, int sy, int ex, int ey){
    vector<vector<bool>> visit(N, vector<bool>(N, false));
    queue<vector<int>> q;
    q.push({sx, sy, 0});
    visit[sx][sy] = true;
    while(!q.empty()){
        vector<int> p = q.front();
        q.pop();
        if(p[0] == ex && p[1] == ey)
            return p[2];
        vector<int> dx = {1, 0, -1, 0};
        vector<int> dy = {0, 1, 0, -1};
        for (int i = 0; i < 4;i++){
            int nx = p[0] + dx[i];
            int ny = p[1] + dy[i];
            if(isValid(nx, ny, N) && !visit[nx][ny] && abs(graph[nx][ny] - graph[p[0]][p[1]]) <= par) {
                visit[nx][ny] = true;
                q.push({nx, ny, p[2] + 1});
            }
        }
    }
    return -1;
}

int main(){
    int T;
    cin >> T;
    while(T--){
        int Q;
        cin >> Q;
        if(Q == 3){
            int N;
            cin >> N;
            vector<vector<int>> graph(N);
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N;j++){
                    int a;
                    cin >> a;
                    if(a)
                        graph[i].push_back(j);
                }
            }
            // TopoSort(graph, N); // O (V + E) Time Complexity
            Lexsmall_Toposort(graph, N); // O((V + E) log V) Time Complexity - optimised
        }
        else {
            int N, par, sx, sy, ex, ey;
            cin >> N >> par >> sx >> sy >> ex >> ey;
            vector<vector<int>> graph(N, vector<int>(N));
            for (int i = 0; i < N;i++){
                for (int j = 0; j < N;j++){
                    cin >> graph[i][j];
                }
            }
            if (Q == 1){
                cout << Dijkstra(graph, N, par, --sx, --sy, --ex, --ey) << endl;
            }
            else{
                cout << BFS(graph, N, par, --sx, --sy, --ex, --ey) << endl;
            }
        }
    }
}
/*
Here I used the VS Code Extension Code Runner Extension to get the ouput of following program
in the terminal and beside this I also run this program using
these commands
gcc A05_Keshav_2020EEB1177_22MCS506.cpp -lstdc++ -o A05_Keshav_2020EEB1177_22MCS506
cmd /c 'A05_Keshav_2020EEB1177_22MCS506 < input.txt > output.txt'
where A05_Keshav_2020EEB1177_22MCS506 is the exe file input.txt is the file containing input and output.txt where we want output

Problem Faced:

When Running Certain Randomly Generated Large Test Cases the code is little prone to break down in middle
which according to my analysis is due to segmentation fault due to accessing the out of bounds space
but I wasn't able to pin point the exact part it was breaking.

But the code works well for the given
i.e.

INPUT:

2
6 9 1
1 2 10
1 3 2
1 4 10
2 3 1
3 4 4
4 5 2
2 6 8
5 2 2
4 6 4
8 13 1
1 2 5
1 5 11
5 2 6
6 5 10
6 2 2
2 3 3
2 7 13
7 6 7
3 7 9
3 4 12
4 8 1
8 3 4
7 8 8

OUTPUT:

14 0 10 2 6 8 10 # 0 5 1 3 4 4
47 0 5 8 20 34 24 17 21 # 0 1 2 3 6 7 3 4

and most of the cases generated at my end.
*/

#include <bits/stdc++.h>
using namespace std;


// Print functions are for debugging purposes
void Print(vector<vector<pair<int, int>>> &adj){
    for (auto i : adj)
    {
        for (auto j : i)
            cout << j.first << " " << j.second << "\t";
        cout << "new "<<endl;
    }
    cout << endl;
}

void Print(vector<int> &arr)
{
    for (auto i : arr)
    {
        cout << i << " ";
    }
    cout << endl;
}

void Print(vector<bool> &arr)
{
    for (auto i : arr)
    {
        cout << i << " ";
    }
    cout << endl;
}

void Print(vector<vector<int>> &vec){
    for(auto i: vec){
        for(auto j: i)
            cout << j << " ";
        cout << endl;
    }
    cout << endl;
}

void Print(set<int> &st){
    for(auto i: st)
        cout << i << " ";
    cout << endl;
}

// Reduce the cost of the incoming edges at each node in the adj matrix
void ReduceCosts(vector<vector<pair<int, int>>> &adj){
    for(auto &i: adj){
        int m = INT_MAX;
        for(auto j: i)
            m = min(m, j.second);
        for(auto &j: i) {
            j.second -= m;
        }
    }
}

// Gives the possible tree which could possibly be an arboroscence
vector<int> Possible_Tree(int N, vector<vector<pair<int, int>>> &adj)
{
    vector<int> ans(N, -1);
    for (int i = 0; i < adj.size();i++)
    {  
        for(auto j: adj[i]){
            if(j.second == 0)
                ans[i] = j.first;
        }
    }
    return ans;
}

// checks if the tree considered has a cycle or not
int ifCycle(vector<int> arr){
    bool ans = true;
    int n = arr.size();
    for (int i = 0; i < n;i++)
    {
        vector<bool> vis(n, false);
        int j = i;
        while(arr[j] != -1 && !vis[j]){
            vis[j] = true;
            j = arr[j];
            if(vis[j]) {
                return j;
            }
        }
    }
    return -1;
}

// Gives the min_cost_arboroscence of the adj matrix
vector<int> Min_Cost_Arboroscence(vector<vector<pair<int, int>>> adj, vector<vector<int>> mat, int n)
{
    ReduceCosts(adj);
    vector<vector<int>> new_mat(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n;i++)
    {
        for(auto j: adj[i]){
            new_mat[j.first][i] = j.second;
        }
    }
    vector<int> ans = Possible_Tree(n, adj);
        // cout << "adj" << endl;
        // Print(adj);
        // Print(ans);
    label:
    if (ifCycle(ans) != -1) {
        set<int> sup_node;
        int j = ifCycle(ans);
        while (sup_node.find(j) == sup_node.end())
        {
            sup_node.insert(j);
            j = ans[j];
        }
        // Print(sup_node);
        vector<vector<pair<int, int>>> new_adj(n + 1);
        // Clustering the super nodes
        for (int i = 0; i < adj.size(); i++)
        {
            if (sup_node.find(i) != sup_node.end())
            {
                for (auto j : adj[i])
                {
                    if (sup_node.find(j.first) == sup_node.end())
                    {
                        new_adj[n].push_back(j);
                    }
                }
            }
            else
            {
                for (auto j : adj[i])
                {
                    if (sup_node.find(j.first) == sup_node.end())
                    {
                        new_adj[i].push_back(j);
                    }
                    else
                        new_adj[i].push_back({n, j.second});
                }
            }
        }
        // Print(new_adj);
        vector<int> arboro = Min_Cost_Arboroscence(new_adj, new_mat, n + 1);
        // Unclustering the super nodes
        for (int i = 0; i < n; i++)
        {
            if (arboro[i] == n)
            {
                int temp = INT_MAX;
                for (auto j : adj[i])
                {
                    if (sup_node.find(j.first) == sup_node.end())
                    {
                        if (j.second < temp)
                        {
                            ans[i] = j.first;
                            temp = j.second;
                        }
                    }
                }
            }
        }
        int par = arboro[n];
        // cout << "par = " << par << endl;
        int temp = INT_MAX;
        // Print(new_mat);
        int p = -1;
        for (auto j : sup_node)
        {
            // cout << "j = " << j << " mat[par][j] = " << new_mat[par][j] << endl;
            if (new_mat[par][j] < temp)
            {
                temp = new_mat[par][j];
                p = j;
            }
        }
        if (p != -1)
            ans[p] = par;
        // cout << "ans" << endl;
        // Print(ans);
    }
    if(ifCycle(ans) != -1)
        goto label;
    return ans;
}

void dfs(vector<vector<int>> &adj, vector<bool> &vis, int node){
    vis[node] = true;
    for(auto i: adj[node]){
        if(!vis[i])
            dfs(adj, vis, i);
    }
}

int main(){
    int testcase;
    cin >> testcase;
    while(testcase--){
        int n, m, s;
        cin >> n >> m >> s;
        vector<vector<pair<int, int>>> adj(n + 1);
        vector<vector<int>> graph(n + 1);
        for (int i = 0; i < m;i++){
            int a, b, w;
            cin >> a >> b >> w;
            adj[b].push_back({a, w});
            graph[a].push_back(b);
        }
        vector<bool> vis(n + 1, false);
        dfs(graph, vis, s);
        vector<vector<pair<int, int>>> nadj(n + 1);
        for (int i = 0; i <= n;i++)
        {
            for(auto &j: adj[i]){
                if(vis[j.first]) {
                    nadj[i].push_back(j);
                }
            }
        }
        adj = nadj;
        vector<vector<int>> mat(n + 1, vector<int>(n + 1, INT_MAX));
        for (int i = 0; i <= n; i++)
        {
            for (auto j : adj[i])
            {
                mat[j.first][i] = j.second;
            }
        }
        vector<int> arboroscence = Min_Cost_Arboroscence(adj, mat, n + 1);
        arboroscence[s] = 0;
        vector<int> dis(n + 1, 0);
        int ans = 0;
        for (int i = 1; i <= n;i++){
            int par = arboroscence[i];
            int child = i;
            if(par == -1){
                dis[i] = -1;
                continue;
            }
            if(par == 0)
                continue;
            // cout << "dis " << mat[par][child] << endl;
            ans += mat[par][child];
            // cout << "i = " << i << endl;
            while(par > 0){
                // cout << "par = " << par << " child = " << child << " dis = " << mat[par][child] << endl;
                dis[i] += mat[par][child];
                child = par;
                par = arboroscence[child];
            }
        }
        cout << ans << " ";
        for (int i = 1; i <= n;i++)
            cout << dis[i] << " ";
        cout << "# ";
        for (int i = 1; i <= n; i++)
            cout << arboroscence[i] << " ";
        cout << endl;
    }
}

// Subject: CS506
// Lab: P05
// Date: 20.11.2021

/*
Approach:
  Min Cost Arborescence using Edmond's Algorithm
Implementation:
  * N Groups are formed. Initially each group contains information of incoming edges in a variable 'par'. The information is stored in following manner:
    par is a vector of pair. First element  -> node number within the group.
                             Second element -> vector of incoming edges to that node. Each incoming edge has format {group number,node number, weight}
  
  * solve is a recursive function which has following arguments
    -> graph: N Groups (as defined above)
    -> ans: for storing final answer (parent node for each node)
    -> active: which groups are active (in case of supernodes, only the lowest node is active, rest are inactive)
  
  * recursive function:
    (1) Find the outgoing edges for each group
    (2) If a group has no incoming edges, mark all the nodes in that group as unreachable (ans=-1) and virtually delete all of its outgoing edges. Recursively repeat the process for the groups connected to its outgoing edges.
    (3) For each group, subtract the lowest incoming edge weight from all incoming edges and select the edge with weight 0 (lexographic order in case of multiple edges). Store it as temp variables of that group.
    (4) Find the cycle. If there exists a cycle, make a new graph with the elements of cycle combined in a single group with group number as the lowest node number in that group. Call the solve again for that graph.
    (5) If a final incoming edge is found for a group (ans) in the solve function, update the information in the group by updating temp variables of that group.
    (6) Update the answer of groups.

  * Now parents are known for each node, so cost of reaching that node could be found using backtracking.
Note:
  * While creating supernode, minimum node value is assigned.
  * If chosing among multiple edges, first lowest destination is preferred, then lowest soruce is preffered.
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long int

ll INF=1e+18;
ll N,M,s;

/* struct for group */
struct NODE{
  vector<pair<ll,vector<vector<ll>>>> par;
  set<ll> out;
  ll temp_from_group,temp_from,temp_to;

  NODE(){
    temp_from_group=temp_from=temp_to=INF;
  }
};

/* function to recursively mark the nodes ureachable from each recursive call of solve function using the out edges */
void mark_unreachable(vector<NODE>& g, vector<vector<ll>>& ans, ll i){
  if (ans[i][0]==-2){
    ll freq=0;
    for (auto it:g[i].par){
      for (auto it2:it.second){
        if (ans[it2[0]][0]!=-1)
          freq++;
      }
    }
    if (freq==0){
      for (auto it:g[i].par){
        ans[it.first][0]=-1;
      }
      for (auto it:g[i].out){
        mark_unreachable(g,ans,it);
      }
    }
  }
}

/* main recursive function for algorithm */
void solve(vector<NODE>& g, vector<vector<ll>>& ans, vector<ll>& active){
  // (1) Update out edges of each group
  for (ll i=1 ; i<=N ; i++){
    if (active[i]){
      for (auto it:g[i].par){
        for (auto it2:it.second){
          g[it2[0]].out.insert(i);
        }
      }
    }
  }

  // (2) No incoming edge to a group -> All the members of a group are unreachable
  for (ll i=1 ; i<=N ; i++){
    if (active[i]){
      mark_unreachable(g,ans,i);
    }
  }

  // (3) Find minimum incoming edge for each group and declare it as temp_from and temp_to
  for (ll i=1 ; i<=N ; i++){
    if (active[i] && ans[i][0]==-2){
      ll mn=INF;
      for (auto it:g[i].par){
        for (auto it2:it.second){
          if (ans[it2[1]][0]!=-1)
            mn=min(mn,it2[2]);
        }
      }
      for (auto& it:g[i].par){
        for (auto& it2:it.second){
          if (ans[it2[1]][0]!=-1){
            it2[2]-=mn;
            if (it2[2]==0){
              if ((it.first<g[i].temp_to) || (it.first==g[i].temp_to && it2[1]<g[i].temp_from)){
                g[i].temp_to=it.first;
                g[i].temp_from=it2[1];
                g[i].temp_from_group=it2[0];
              }
            }
          }
        }
      }
    }
  }

  // (4) Find cylce
  ll cycle=0;
  for (ll i=1 ; i<=N ; i++){
    if (active[i]){
      ll cur=i;
      vector<bool> vis(N+1,0);
      while (cur!=INF){
        if (vis[cur]){
          cycle=cur;
          break;
        }
        vis[cur]=1;
        cur=g[cur].temp_from_group;
      }
    }
    if (cycle) break;
  }

  if (cycle){
    vector<bool> in_cycle(N+1,0);
    ll cur=cycle;
    do{
      in_cycle[cur]=1;
      cur=g[cur].temp_from_group;
    } while (cur!=cycle);

    vector<NODE> g2(N+1);
    vector<ll> active2;
    active2=active;

    ll group=0;
    for (ll i=1 ; i<=N ; i++) {
      if (in_cycle[i]){
        if (group==0)
          group=i;
        else
          active2[i]=0;
        for (auto it:g[i].par){
          pair<ll,vector<vector<ll>>> temp;
          temp.first = it.first;
          for (auto it2:it.second){
            if (!in_cycle[it2[0]]){
              temp.second.push_back(it2);
            }
          }
          g2[group].par.push_back(temp);
        }
      }
    }

    for (ll i=1 ; i<=N ; i++) {
      if (!in_cycle[i] && active[i]){
        g2[i].par=g[i].par;
        for (auto& it:g2[i].par){
          for (auto& it2:it.second){
            if (in_cycle[it2[0]]) it2[0]=group;
          }
        }
      }
    }

    solve(g2,ans,active2);
  }

  // (5) Remove temporary info if an incoming edge is already found for a node in that group
  for (ll i=1 ; i<=N ; i++){
    if (active[i]){
      for (auto it:g[i].par){
        if (ans[it.first][0]!=-2) g[i].temp_to=INF;
      }
    }
  }

  // (6) Update answer for all the active groups
  for (ll i=1 ; i<=N ; i++){
    if (active[i] && g[i].temp_to!=INF && ans[g[i].temp_to][0]==-2){
      ans[g[i].temp_to][0] = g[i].temp_from;
    }
  }
}

/* recursive function to calculate cost to reach a node from root, given parents of each node and adjacency matrix */
void calculate_cost_from_root(vector<vector<ll>>& adj, vector<vector<ll>>& ans, ll cur){
  if (ans[cur][1]!=-2) return;
  if (ans[cur][0]==-1) {ans[cur][1]=-1; return;}
  calculate_cost_from_root(adj,ans,ans[cur][0]);
  ans[cur][2]=adj[ans[cur][0]][cur];
  ans[cur][1]=ans[ans[cur][0]][1]+ans[cur][2];
}

int main(){
  ll t;
  cin >> t;
  while (t--){
    ll u,v,w,ans=1;
    cin >> N >> M >> s;

    vector<vector<ll>> adj(N+1,vector<ll>(N+1,INF));
    vector<NODE> g(N+1);

    for (ll i=0 ; i<M ; i++){
      cin >> u >> v >> w;
      adj[u][v]=min(adj[u][v],w);
      if (w<0) ans=0;
    }

    if (ans){
      for (ll i=1 ; i<=N ; i++){
        g[i].par.push_back({i,{}});
      }
      for (ll i=1 ; i<=N ; i++){
        for (ll j=1 ; j<=N ; j++){
          if (i!=j && adj[i][j]!=INF){
            g[j].par[0].second.push_back({i,i,adj[i][j]});
          }
        }
      }
      vector<vector<ll>> ans(N+1,vector<ll>(3,-2)); // [0]->parent [1]->cost_from_root [2]->cost_from_parent
      vector<ll> active(N+1,1); // which groups are active. nodes in supernodes are inactive.
      ans[s][0]=ans[s][1]=0;
      active[s]=0;
      solve(g,ans,active);
      ll tot=0;
      for (ll i=1 ; i<=N ; i++){
        if (i!=s){
          calculate_cost_from_root(adj,ans,i);
          if (ans[i][2]>0) tot+=ans[i][2];
        }
      }
      cout << tot << " ";
      for (ll i=1 ; i<=N ; i++) cout << ans[i][1] << " ";
      cout << "# ";
      for (ll i=1 ; i<=N ; i++) cout << ans[i][0] << " ";
    }
    else{
      cout << -1;
    }
    cout << endl;
  }
  return 0;
}

/*
Inputs/Outputs tested (excluding provided):
<INPUT START>
5
1
9 14 1
1 2 5
2 3 1
3 4 1
4 5 1
5 2 1
6 7 1
7 8 1
8 9 1
9 6 1
3 7 7
3 6 8
3 9 10
4 9 6
8 5 4
1
7 7 1
1 2 10
2 3 10
4 3 1
5 4 1
6 5 1
7 6 1
5 7 1

5 8 1
1 3 10
1 4 10
1 5 2
2 3 1
3 4 1
4 2 1
5 4 10
5 3 10

6 14 1
6 2 10
5 2 10
4 2 5
2 3 6
1 3 11
4 3 7
5 3 11
2 4 9
1 4 12
6 4 12
3 4 7
5 4 13
1 5 1
1 6 1
1
7 8 3
7 5 10
5 6 10
6 7 10
4 1 10
1 2 10
2 4 10
4 6 100
3 2 100
<INPUT END>

<OUTPUT START>
17 0 5 6 7 8 14 15 16 13 # 0 1 2 3 4 9 6 7 4 
20 0 10 20 -1 -1 -1 -1 # 0 1 2 -1 -1 -1 -1 
14 0 12 10 11 2 # 0 4 1 3 1 
25 0 11 17 24 1 1 # 0 5 2 3 1 1 
240 120 100 0 110 230 210 220 # 4 3 0 2 7 4 6
<OUTPUT END>
*/
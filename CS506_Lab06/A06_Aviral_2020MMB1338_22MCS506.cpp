#include <iostream>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;


void insert(pair<int,int> p,int &size,vector<pair<int,int>> &heap,unordered_map<int,int> &map){
    size++;
    heap[size]=p;
    map[p.second]=size;
    int i=size;
    while(i>1){
        int parent=i/2;
        if(heap[parent].first<heap[i].first){
            swap(map[(heap[parent]).second],map[(heap[i].second)]);
            swap(heap[parent],heap[i]);
            i=parent;
        }
        else{
            return;
        }
    }
}

void heapify(int i,int &size,vector<pair<int,int>> &heap,unordered_map<int,int> &map){
    int smallest=i;
    int left=2*i;
    int right=2*i+1;
    if(left<=size && heap[smallest].first>heap[left].first){
        smallest=left;
    }
    if(right<=size && heap[smallest].first>heap[right].first){
        smallest=right;
    }
    if(smallest!=i){
        swap(map[(heap[smallest]).second],map[(heap[i]).second]);
        swap(heap[smallest],heap[i]);
        i=smallest;
        heapify(i,size,heap,map);
    }
}

pair<int,int> delete_min(int &size,vector<pair<int,int>> &heap,unordered_map<int,int> &map){
    pair<int,int> minimum=heap[1];
    swap(map[(heap[1].second)],map[(heap[size]).second]);
    swap(heap[1],heap[size]);
    map[(heap[size].second)]=-1;
    size--;
    heapify(1,size,heap,map);
    return minimum;
}

void dec_key(int v,int w,int size,vector<pair<int,int>> &heap,unordered_map<int,int> &map){
    int i=map[v];
    heap[i].second=w;
    while(i>1){
        int parent=i/2;
        if(heap[parent].first<heap[i].first){
            swap(map[(heap[parent]).second],map[(heap[i].second)]);
            swap(heap[parent],heap[i]);
            i=parent;
        }
        else{
            return;
        }
    }
}

bool empty(int size){
    if(size==0){
        return true;
    }
    return false;
}



struct binomial_heap{
    int vertex, wt;
    int rank;
    binomial_heap *parent,*child,*next;

    binomial_heap(int v,int w){
        vertex=v;
        wt=w;
        rank=0;
        parent=child=next=NULL;
    }
};

binomial_heap* meld_bin(binomial_heap* heap1,binomial_heap* heap2){
    if(!heap1 && !heap2){
        return NULL;
    }
    if(!heap1){
        return heap2;
    }
    if(!heap2){
        return heap1;
    }

    binomial_heap *temp1,*temp2;
    if(heap1->rank<=heap2->rank){
        temp1=heap1;
        temp2=heap1;
        heap1=heap1->next;
    }
    else{
        temp1=heap2;
        temp2=heap2;
        heap2=heap2->next;
    }
    while(heap1 && heap2){
        if(heap1->rank<=heap2->rank){
            temp2->next=heap1;
            temp2=heap1;
            heap1=heap1->next;
        }
        else{
            temp2->next=heap2;
            temp2=heap2;
            heap2=heap2->next;
        }
    }
    if(heap1 && !heap2){
        temp2->next=heap1;
    }
    else if(!heap1 && heap2){
        temp2->next=heap2;
    }

    binomial_heap* joined=temp1;
    binomial_heap* prev=NULL,*cur=joined,*nxt=joined->next;
    while(true){
        if(cur->rank==nxt->rank && (!nxt->next || (nxt->next && nxt->rank!=nxt->next->rank))){
            if(cur->wt>nxt->wt){
                if(!prev){
                    joined=nxt;
                }
                else{
                    prev->next=nxt;
                }
                cur->next=nxt->child;
                nxt->child=cur;
                cur->parent=nxt;
                (nxt->rank)++;
                cur=nxt;
            }
            else{
                cur->next=nxt->next;
                nxt->next=cur->child;
                cur->child=nxt;
                nxt->parent=cur;
                (cur->rank)++;
            }
            nxt=cur->next;
        }
        else{
            prev=cur;
            cur=cur->next;
            nxt=nxt->next;
        }
        if(!nxt){
            break;
        }
    }
    return joined;
}

binomial_heap* insert_bin(binomial_heap* heap,int v,int w,unordered_map<int,binomial_heap*> &bin_map){
    binomial_heap* temp=new binomial_heap(v,w);
    bin_map[v]=temp;
    return meld_bin(heap,temp);
}

binomial_heap* extract_min_bin(binomial_heap* heap,int &v,int &w){
    binomial_heap *temp1=heap->next,*mini=heap,*prev=heap,*temp2=NULL;
    if(temp1){
        while(temp1){
            if(temp1->wt<mini->wt){
                mini=temp1;
                temp2=prev;
            }
            prev=temp1;
            temp1=temp1->next;
        }
    }
    else{
        heap=NULL;
    }

    if(!temp2){
        heap=mini->next;
    }
    else{
        temp2->next=mini->next;
    }
    v=mini->vertex;
    w=mini->wt;

    if(!mini->child){
        mini->next=NULL;
        free(mini);
        return heap;
    }

    prev=NULL;
    temp1=mini->child;
    binomial_heap* temp3=NULL;
    while(temp1){
        temp1->parent=NULL;
        temp3=temp1->next;
        temp1->next=prev;
        prev=temp1;
        temp1=temp3;
    }
    mini->child=NULL;
    mini->next=NULL;
    free(mini);
    return meld_bin(heap,prev);
}

void dec_key_bin(int v,int w,unordered_map<int,binomial_heap*> bin_map){
    binomial_heap* node=bin_map[v];
    node->wt=w;
    binomial_heap* p=node->parent;
    binomial_heap* temp;
    while(p && w<p->wt){
        swap(p->wt,node->wt);
        temp=bin_map[node->vertex];
        bin_map[node->vertex]=bin_map[p->vertex];
        bin_map[p->vertex]=temp;
        swap(p->vertex,node->vertex);
        node=p;
        p=p->parent;
    }
}



struct fibonacci_heap{
    int vertex,wt;
    int rank;
    bool mark;
    fibonacci_heap* parent,*child,*left,*right;

    fibonacci_heap(int v,int w){
        vertex=v;
        wt=w;
        mark=false;
        rank=0;
        parent=child=left=right=NULL;
    }
};


fibonacci_heap* insert_fib(fibonacci_heap* heap,int v,int w,unordered_map<int,fibonacci_heap*> &fib_map){
    fibonacci_heap* temp=new fibonacci_heap(v,w);
    fib_map[v]=temp;
    temp->left=temp->right=temp;

    if(heap==NULL){
        heap=temp;
    }
    else{
        fibonacci_heap *temp1=heap->left;
        temp1->right=temp;
        heap->left=temp;
        temp->left=temp1;
        temp->right=heap;
    }

    if(w<heap->wt){
        heap=temp;
    }
    return heap;
}

fibonacci_heap* merge_fib(fibonacci_heap* heap1,fibonacci_heap* heap2){
    fibonacci_heap* mini,*maxi;
    if(heap1->wt>heap2->wt){
        maxi=heap1;
        mini=heap2;
    }
    else{
        maxi=heap2;
        mini=heap1;
    }

    fibonacci_heap* temp1,*temp2;
    temp1=mini->right;
    mini->right=maxi;
    temp2=maxi->left;
    maxi->left=mini;
    temp1->left=temp2;
    temp2->right=temp1;

    return mini;
}

fibonacci_heap* extract_min_fib(fibonacci_heap* heap){
    if(heap->child){
        fibonacci_heap* temp=heap->child;
        while(true){
            temp->parent=NULL;
            temp->mark=false;
            temp=temp->right;
            if(temp==heap->child){
                break;
            }
        }
    }

    if(!heap->child && heap->right==heap){
        heap->left=NULL;
        heap->right=NULL;
        free(heap);
        return NULL;
    }
    else if(heap->right!=heap){
        fibonacci_heap* temp=heap;
        heap->left->right=heap->right;
        heap->right->left=heap->left;
        if(heap->child){
            heap=merge_fib(heap->child,heap->right);
        }
        else{
            heap=heap->right;
        }
        temp->child=NULL;
        temp->left=NULL;
        temp->right=NULL;
        free(temp);
    }
    else{
        fibonacci_heap* temp=heap;
        heap=heap->child;
        temp->child=NULL;
        temp->left=NULL;
        temp->right=NULL;
        free(temp);
    }

    unordered_map<int,fibonacci_heap*> rank_map;
    fibonacci_heap *dup=rank_map[heap->rank];
    while(dup!=heap){
        if(!dup){
            rank_map[heap->rank]=heap;
            heap=heap->right;
        }
        else{
            if(dup->wt>=heap->wt){
                dup->left->right=dup->right;
                dup->right->left=dup->left;
                dup->left=dup;
                dup->right=dup;
                dup->parent=heap;
                (heap->rank)++;
                if(!heap->child){
                    heap->child=dup;
                }
                else{
                    heap->child=merge_fib(heap->child,dup);
                }
            }
            else{
                if(heap->left==dup && heap->right==dup){
                    dup->left->right=dup->right;
                    dup->right->left=dup->left;
                    dup->left=heap->left;
                    dup->right=heap->right;
                }
                heap->left->right=dup;
                heap->right->left=dup;
                heap->left=heap;
                heap->right=heap;
                heap->parent=dup;
                (dup->rank)++;
                if(!dup->child){
                    dup->child=heap;
                }
                else{
                    dup->child=merge_fib(dup->child,heap);
                }
                heap=dup;
            }
        }
        
        dup=rank_map[heap->rank];
        rank_map[heap->rank]=NULL;
    }

    fibonacci_heap* temp1=heap->right,*temp2=heap;
    while(temp1!=heap){
        if(temp1->wt<temp2->wt){
            temp2=temp1;
        }
        temp1=temp1->right;
    }
    return temp2;
}

fibonacci_heap* dec_key_fib(fibonacci_heap* heap,int v,int w,unordered_map<int,fibonacci_heap*> fib_map){
    fibonacci_heap* node =fib_map[v];
    node->wt=w;
    if(!node->parent || w>=node->parent->wt){
        if(heap->wt>w){
            heap=node;
        }
        return heap;
    }
    fibonacci_heap* temp;
    do{
        node->left->right=node->right;
        node->right->left=node->left;
        if(node->right!=node){
            node->parent->child=node->right;
        }
        else{
            node->parent->child=NULL;
        }
        node->mark=false;
        node->left=node->right=node;
        (node->parent->rank)--;
        temp=node->parent;
        node->parent=NULL;
        heap=merge_fib(heap,node);
        node=temp;
    }while(node->mark && node->parent);

    if(node->parent){
        node->mark=true;
    }
    return heap;
}


void dijkstra_array(int src,int n,vector<vector<int>> &dist,unordered_map<int,list<pair<int,int>>> adj){
    vector<bool> visited(n+1,false);
    int count=0;
    dist[src][src]=0;
    count++;
    while(count){
        int u;
        int minimum=999999;
        for(int i=1;i<=n;i++){
            if(!visited[i]){
                if(dist[src][i]<minimum){
                    minimum=dist[src][i];
                    u=i;
                }
            }
        }
        visited[u]=true;
        count--;
        for(auto v:adj[u]){
            if(dist[src][u]+v.second<dist[src][v.first]){
                if(dist[src][v.first]==999999){
                    count++;
                }
                dist[src][v.first]=dist[src][u]+v.second;
            }
        }
    }
}


void dijkstra_binary_heap(int src,int n,vector<vector<int>> &dist,unordered_map<int,list<pair<int,int>>> adj){

    dist[src][src]=0;
    vector<pair<int,int>> heap(n+1); // pair of (edge weight,vertex)
    unordered_map<int,int> map;
    pair<int,int> p;
    p.first=0;
    p.second=src;
    int size=0;
    insert(p,size,heap,map);

    while(!empty(size)){
        pair<int,int> u=delete_min(size,heap,map);
        for(auto v:adj[u.second]){
            if(dist[src][u.second]+v.second<dist[src][v.first]){
                if(map[(heap[v.first]).second]==0){
                    dist[src][v.first]=dist[src][u.second]+v.second;
                    insert(make_pair(dist[src][v.first],v.first),size,heap,map);
                }
                else{
                    dist[src][v.first]=dist[src][u.second]+v.second;
                    dec_key(v.first,dist[src][v.first],size,heap,map);
                }
                
            }
        }
    }
}


void dijkstra_bin(int src,int n,vector<vector<int>> &shortest_dist,unordered_map<int,list<pair<int,int>>> adj){

    binomial_heap* heap=NULL;
    unordered_map<int,binomial_heap*> bin_map;
    shortest_dist[src][src]=0;
    heap=insert_bin(heap,src,0,bin_map);

    while(heap){
        int u,w;
        heap=extract_min_bin(heap,u,w);
        for(auto v:adj[u]){
            if(shortest_dist[src][v.first]>shortest_dist[src][u]+v.second){
                if(shortest_dist[src][v.first]==999999){
                    shortest_dist[src][v.first]=shortest_dist[src][u]+v.second;
                    heap=insert_bin(heap,v.first,shortest_dist[src][v.first],bin_map);
                }
                else{
                    shortest_dist[src][v.first]=shortest_dist[src][u]+v.second;
                    dec_key_bin(v.first,shortest_dist[src][v.first],bin_map);
                }
            }
        }
    }
}


void dijkstra_fib(int src,int n,vector<vector<int>> &shortest_dist,unordered_map<int,list<pair<int,int>>> adj){

    fibonacci_heap* heap=NULL;
    unordered_map<int,fibonacci_heap*> fib_map;
    shortest_dist[src][src]=0;
    heap=insert_fib(heap,src,0,fib_map);

    while(heap){
        int u=heap->vertex;
        fib_map[u]=NULL;
        heap=extract_min_fib(heap);
        for(auto v:adj[u]){
            if(shortest_dist[src][v.first]>shortest_dist[src][u]+v.second){
                if(shortest_dist[src][v.first]==999999){
                    shortest_dist[src][v.first]=shortest_dist[src][u]+v.second;
                    heap=insert_fib(heap,v.first,shortest_dist[src][v.first],fib_map);
                }
                else{
                    shortest_dist[src][v.first]=shortest_dist[src][u]+v.second;
                    heap=dec_key_fib(heap,v.first,shortest_dist[src][v.first],fib_map);
                }
            }
        }
    }
}


int main(){

    int t;
    cin>>t;
    int x=0;
    vector<double> time_spent(t,0);
    clock_t time;
    while(t--){
        
        int n,d,a;      // using a for defining which heap implementation to use
        cin>>n>>d>>a;   // taking a as input along with n and d
        unordered_map<int,list<pair<int,int>>> adj;  // pair of (vertex,edge weight)
        bool negative=false;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                int w;
                cin>>w;
                if(w<999999){
                    if(w<0){
                        negative=true;
                    }
                    adj[i].push_back(make_pair(j,w));
                    if(d==0){
                        adj[j].push_back(make_pair(i,w));
                    }
                }
            }
        }

        if(negative){
            for(int i=0;i<=n;i++){
                adj[n+1].push_back(make_pair(i,0));
            }
            vector<int> h(n+2,999999);
            h[n+1]=0;
            for(int i=0;i<n;i++){
                for(int u=1;u<=n+1;u++){
                    for(auto v:adj[u]){
                        if(v.second+h[u]<h[v.first]){
                            h[v.first]=h[u]+v.second;
                        }
                    }
                }
            }

            vector<bool> negative_cycle(n+1,false);
            for(int i=1;i<=n+1;i++){
                for(auto j:adj[i]){
                    if(h[i]+j.second<h[j.first]){
                        negative_cycle[i]=true;
                        if(d==0){
                            negative_cycle[j.first]=true;
                        }
                        else{
                            for(auto k:adj[j.first]){
                                if(k.first==i){
                                    negative_cycle[j.first]=true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }


            for(int u=1;u<=n;u++){
                for(auto v:adj[u]){
                    v.second+=(h[u]-h[v.first]);
                }
            }

            vector<vector<int>> dist(n+1);
            for(int i=1;i<=n;i++){
                dist[i]=vector<int>(n+1,999999);
            }

            time=clock();
            for(int i=1;i<=n;i++){

                if(a==1 && !negative_cycle[i]){
                    dijkstra_array(i,n,dist,adj);
                }
                else if(a==2 && !negative_cycle[i]){
                    dijkstra_binary_heap(i,n,dist,adj);
                }
                else if(a==3 && !negative_cycle[i]){
                    dijkstra_bin(i,n,dist,adj);
                }
                else if(!negative_cycle[i]){
                    dijkstra_fib(i,n,dist,adj);    // using fibonacci heap implementation for a=4 or if no choice given 
                }

            }
            time = clock()-time;
            double time_taken = ((double)time)/CLOCKS_PER_SEC;
            time_spent[x]=time_taken;

            for(int i=1;i<=n;i++){
                if(negative_cycle[i] || dist[i][i]<0){
                    cout<<"-1"<<endl;;
                    continue;
                }
                for(int j=1;j<=n;j++){
                    cout<<dist[i][j]<<" "; 
                }
                cout<<endl;
            }
        }
        else{
            vector<vector<int>> dist(n+1);
            for(int i=1;i<=n;i++){
                dist[i]=vector<int>(n+1,999999);
            }

            time=clock();
            for(int i=1;i<=n;i++){

                if(a==1){
                    dijkstra_array(i,n,dist,adj);
                }
                else if(a==2){
                    dijkstra_binary_heap(i,n,dist,adj);
                }
                else if(a==3){
                    dijkstra_bin(i,n,dist,adj);
                }
                else{
                    dijkstra_fib(i,n,dist,adj);
                }

            }
            time = clock()-time;
            double time_taken = ((double)time)/CLOCKS_PER_SEC;
            time_spent[x]=time_taken;

            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    cout<<dist[i][j]<<" ";                   
                }
                cout<<endl;
            }
        }
        x++;
    }

    for(int i=0;i<x;i++){
        cout<<time_spent[i]<<" ";
    }
    cout<<endl;

    return 0;
}



/*
   using "a" variable for defining which heap implementation to use
   and taking it as an input along with n and d foe each test case 

*/
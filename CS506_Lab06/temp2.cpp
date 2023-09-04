#include <bits/stdc++.h>
#include <time.h>
#define INF 999999
using namespace std;

// Prototype of a utility function to swap two integers
void swap(pair<int,int> *x, pair<int,int> *y)
{
    pair<int,int> temp = *x;
    *x = *y;
    *y = temp;
}

class BinaryHeap
{
    pair<int,int> *harr;     // pointer to array of elements in heap
    int capacity;  // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }

public:
    // Constructor
    BinaryHeap(int cap)
    {
        heap_size = 0;
        capacity = cap;
        harr = new pair<int,int>[cap];
    }

    // to heapify a subtree with the root at given index
    void MinHeapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < heap_size && harr[l] < harr[i])
            smallest = l;
        if (r < heap_size && harr[r] < harr[smallest])
            smallest = r;
        if (smallest != i)
        {
            swap(&harr[i], &harr[smallest]);
            MinHeapify(smallest);
        }
    }
    // to extract the root which is the minimum element
    pair<int,int> Extract_min()
    {
        if (heap_size <= 0)
            return {-1,-1};
        if (heap_size == 1)
        {
            heap_size--;
            return harr[0];
        }

        // Store the minimum value, and remove it from heap
        pair<int,int> root = harr[0];
        harr[0] = harr[heap_size - 1];
        heap_size--;
        MinHeapify(0);

        return root;
    }

    // Returns the minimum key (key at root) from min heap
    pair<int,int> getMin() { return harr[0]; }

    // Inserts a new key 'k'
    void Insert(pair<int,int> k)
    {
        if (heap_size == capacity)
        {
            cout << "\nOverflow: Could not insertKey\n";
            return;
        }

        // First insert the new key at the end
        heap_size++;
        int i = heap_size - 1;
        harr[i] = k;

        // Fix the min heap property if it is violated
        while (i != 0 && harr[parent(i)] > harr[i])
        {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }

    bool empty(){
        return (heap_size <= 0);
    }
};

class Fibonacci_Heap
{
private:
    struct node
    {
        node *parent, *child, *left, *right;
        int val, deg, nd;
        char mark, c;
    };

    struct node *minptr = NULL;
    int num = 0;

    node *new_node(pair<int, int> p)
    {
        struct node *temp = new node();
        temp->val = p.first;
        temp->nd = p.second;
        temp->deg = 0;
        temp->mark = 'W';
        temp->c = 'N';
        temp->parent = NULL;
        temp->child = NULL;
        temp->left = temp;
        temp->right = temp;
    }

public:
    // Function to insert a node in heap
    void Insert(pair<int, int> p)
    {
        struct node *temp = new_node(p);

        // Inserting node before min node
        if (minptr != NULL)
        {
            (minptr->left)->right = temp;
            temp->right = minptr;
            temp->left = minptr->left;
            minptr->left = temp;
            if (temp->val < minptr->val)
                minptr = temp;
        }
        else
            minptr = temp;
        num++;
    }

    // Linking the heap nodes in parent child relationship
    void Connect(struct node *n1, struct node *n2)
    {
        (n2->left)->right = n2->right;
        (n2->right)->left = n2->left;

        if (n1->right == n1)
            minptr = n1;

        n2->left = n2;
        n2->right = n2;
        n2->parent = n1;

        if (n1->child == NULL)
            n1->child = n2;

        n2->right = n1->child;
        n2->left = (n1->child)->left;
        ((n1->child)->left)->right = n2;
        (n1->child)->left = n2;

        if (n2->val < (n1->child)->val)
            n1->child = n2;
        n1->deg++;
    }

    // Consolidating the heap
    void Consolidate()
    {
        int temp1;
        int temp3 = (log(num)) / (log(2));
        struct node *arr[temp3 + 1];
        for (int i = 0; i <= temp3; i++)
            arr[i] = NULL;

        node *n1 = minptr, *n2, *n3, *n4 = n1;
        do
        {
            n4 = n4->right;
            temp1 = n1->deg;
            while (arr[temp1] != NULL)
            {
                n2 = arr[temp1];
                if (n1->val > n2->val)
                {
                    n3 = n1;
                    n1 = n2;
                    n2 = n3;
                }
                if (n2 == minptr)
                    minptr = n1;
                Connect(n1, n2);
                if (n1->right == n1)
                    minptr = n1;
                arr[temp1] = NULL;
                temp1++;
            }
            arr[temp1] = n1;
            n1 = n1->right;
        } while (n1 != minptr);
        minptr = NULL;

        for (int j = 0; j <= temp3; j++)
        {
            if (arr[j] != NULL)
            {
                arr[j]->left = arr[j];
                arr[j]->right = arr[j];
                if (minptr != NULL)
                {
                    (minptr->left)->right = arr[j];
                    arr[j]->right = minptr;
                    arr[j]->left = minptr->left;
                    minptr->left = arr[j];
                    if (arr[j]->val < minptr->val)
                        minptr = arr[j];
                }
                else
                {
                    minptr = arr[j];
                }
                if (minptr == NULL)
                    minptr = arr[j];
                else if (arr[j]->val < minptr->val)
                    minptr = arr[j];
            }
        }
    }

    // Function to extract minptrmum node in the heap
    pair<int, int> Extract_min()
    {
        pair<int, int> ans = {-1, -1};
        if (minptr == NULL)
            cout << "The heap is empty" << endl;
        else
        {
            node *temp = minptr;
            ans = {minptr->val, minptr->nd};
            node *pntr;
            pntr = temp;
            node *x = NULL;
            if (temp->child != NULL)
            {
                x = temp->child;
                do
                {
                    pntr = x->right;
                    (minptr->left)->right = x;
                    x->right = minptr;
                    x->left = minptr->left;
                    minptr->left = x;
                    if (x->val < minptr->val)
                        minptr = x;
                    x->parent = NULL;
                    x = pntr;
                } while (pntr != temp->child);
            }
            (temp->left)->right = temp->right;
            (temp->right)->left = temp->left;
            minptr = temp->right;
            if (temp == temp->right && temp->child == NULL)
                minptr = NULL;
            else
            {
                minptr = temp->right;
                Consolidate();
            }
            num--;
        }
        return ans;
    }

    bool empty(){
        return (minptr == NULL);
    }
};

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

                if (dist[u] != INF && dist[u] + wt < dist[v])
                {
                    dist[v] = dist[u] + wt;
                    par[v] = u;
                    x = v;
                }
            }
        }
    }

    if (x != -1)
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

        for (auto i : cycle)
        {
            dist[i] = INF;
        }
    }
    return dist;
}

vector<vector<int>> Dijkstra(int V, vector<pair<int, int>> adj[], set<int> cycle)
{
    vector<vector<int>> dist(V, vector<int>(V, INF));
    // priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    Fibonacci_Heap q = Fibonacci_Heap();
    // BinaryHeap q = BinaryHeap(V*V);

    for (int i = 0; i < V; i++)
    {
        int src = i;
        if (cycle.find(src) != cycle.end())
        {
            continue;
        }
        dist[i][i] = 0;
        q.Insert({0, src});
        // q.push({0, src});

        while (!q.empty())
        {
            pair<int, int> p = q.Extract_min();
            // pair<int, int> p = q.top();
            // q.pop();
            int node = p.second;
            int currDist = p.first;
            // q.pop();
            if (dist[i][node] < currDist)
                continue;
            for (auto x : adj[node])
            {
                int ver = x.first;
                int wt = x.second;
                if (cycle.find(ver) == cycle.end() && wt + dist[i][node] < dist[i][ver])
                {
                    dist[i][ver] = wt + dist[i][node];
                    q.Insert({dist[i][ver], ver});
                    // q.push({dist[i][ver], ver});
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
            if (h[u] == INF || h[adj[u][v].first] == INF)
                continue;
            adj[u][v].second = adj[u][v].second + h[u] - h[adj[u][v].first];
        }
    }

    set<int> cycle;
    for (int i = 0; i < V; i++)
    {
        if (h[i] == INF)
            cycle.insert(i);
    }

    vector<vector<int>> SP = Dijkstra(V, adj, cycle);

    for (int u = 0; u < V; u++)
    {
        for (int v = 0; v < V; v++)
        {
            if (SP[u][v] == INF)
                continue;
            SP[u][v] = SP[u][v] + h[v] - h[u];
        }
    }

    for (int u = 0; u < V; u++)
    {
        if (cycle.find(u) != cycle.end())
        {
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
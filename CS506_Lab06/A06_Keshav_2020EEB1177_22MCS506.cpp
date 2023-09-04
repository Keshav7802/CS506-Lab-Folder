/*
Here I used the VS Code Extension Code Runner Extension to get the ouput of following program
in the terminal and beside this I also run this program using these commands
    gcc A06_Keshav_2020EEB1177_22MCS506.cpp -lstdc++ - o A06_Keshav_2020EEB1177_22MCS506
    cmd / c 'A06_Keshav_2020EEB1177_22MCS506 1 < input.txt > output1.txt'
    cmd / c 'A06_Keshav_2020EEB1177_22MCS506 2 < input.txt > output2.txt'
    cmd / c 'A06_Keshav_2020EEB1177_22MCS506 3 < input.txt > output3.txt'
    cmd / c 'A06_Keshav_2020EEB1177_22MCS506 4 < input.txt > output4.txt'
where A05_Keshav_2020EEB1177_22MCS506 is the exe file input.txt is the file containing input and output.txt where we want output

Test Case Used:
4
4 1
0 999999 999999 2
6 0 3 999999
4 999999 0 5
999999 -7 -3 0
4 1
0 -3 999999 2
5 0 3 999999
1 999999 0 999999
-1 999999 4 0
4 1
0 -5 2 3
999999 0 4 999999
999999 999999 0 1
999999 999999 999999 0
4 1
0 -4 999999 999999
3 0 999999 999999
999999 999999 0 2
999999 999999 -1 0

Output:

output1
0 -5 -2 2
6 0 3 8
4 -2 0 5
-1 -7 -4 0
0 -3 0 2
4 0 3 6
1 -2 0 3
-1 -4 -1 0
0 -5 -1 0
999999 0 4 5
999999 999999 0 1
999999 999999 999999 0
-1
-1
999999 999999 0 2
999999 999999 -1 0
0 0.001 0 0


output2
0 -5 -2 2
6 0 3 8
4 -2 0 5
-1 -7 -4 0
0 -3 0 2
4 0 3 6
1 -2 0 3
-1 -4 -1 0
0 -5 -1 0
999999 0 4 5
999999 999999 0 1
999999 999999 999999 0
-1
-1
999999 999999 0 2
999999 999999 -1 0
0 0 0 0

output3
0 -5 -2 2
6 0 3 8
4 -2 0 5
-1 -7 -4 0
0 -3 0 2
4 0 3 6
1 -2 0 3
-1 -4 -1 0
0 -5 -1 0
999999 0 4 5
999999 999999 0 1
999999 999999 999999 0
-1
-1
999999 999999 0 2
999999 999999 -1 0
0 0 0 0

output4
0 -5 -2 2
6 0 3 8
4 -2 0 5
-1 -7 -4 0
0 -3 0 2
4 0 3 6
1 -2 0 3
-1 -4 -1 0
0 -5 -1 0
999999 0 4 5
999999 999999 0 1
999999 999999 999999 0
-1
-1
999999 999999 0 2
999999 999999 -1 0
0 0 0.001 0


Problem Faced:
The code was initially giving time analyzed for the given testcase but when I used the same code for analyzing it for large testcases
like 300 - 10000. From then it starts giving zero time but, the code is giving correcti APSP and also gives correct results when
analyzed for large graphs.

*/

#include <bits/stdc++.h>
#include <time.h>
#define INF 999999
using namespace std;

class BinaryHeap
{
    pair<int, int> *harr; 
    int *ptr; 
    int cap; 
    int heap_size;       

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }

public:
    // Constructor
    BinaryHeap(int c)
    {
        heap_size = 0;
        cap = c;
        harr = new pair<int, int>[cap];
        ptr = new int[cap];
    }

    // Swapping the Nodes for Percolate Up and Percolate Down
    void swap(pair<int, int> *x, pair<int, int> *y, int xi, int yi)
    {
        ptr[(*y).second] = xi;
        ptr[(*x).second] = yi;
        pair<int, int> temp = *x;
        *x = *y;
        *y = temp;
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
            swap(&harr[i], &harr[smallest], i, smallest);
            MinHeapify(smallest);
        }
    }

    // to extract the root which is the minimum element
    pair<int, int> extractMin()
    {
        if (heap_size <= 0)
            return {-1, -1};
        if (heap_size == 1)
        {
            heap_size--;
            return harr[0];
        }

        // Store the minimum value, and remove it from heap
        pair<int, int> root = harr[0];
        harr[0] = harr[heap_size - 1];
        heap_size--;
        MinHeapify(0);

        return root;
    }

    // Returns the minimum key (key at root) from min heap
    pair<int, int> getMin() { return harr[0]; }

    // Inserts a new key 'k'
    void insertKey(int k, int wt)
    {
        if (heap_size == cap)
        {
            cout << "\nOverflow: Could not insertKey\n";
            return;
        }

        // First insert the new key at the end
        heap_size++;
        int i = heap_size - 1;
        ptr[k] = i;
        harr[i] = {wt, k};

        // Fix the min heap property if it is violated
        while (i != 0 && harr[parent(i)] > harr[i])
        {
            swap(&harr[i], &harr[parent(i)], i, parent(i));
            i = parent(i);
        }
    }

    void decreaseKey(int v, int newValue)
    {
        int i = ptr[v];
        harr[i].first = newValue;
        while (i != 0 && harr[parent(i)] > harr[i])
        {
            swap(&harr[i], &harr[parent(i)], i, parent(i));
            i = parent(i);
        }
    }

    bool empty()
    {
        return (heap_size <= 0);
    }
};

class BinomialHeap
{
    typedef struct unit
    {
        int wt;
        int deg;
        int node;
        unit *parent, *child, *sibling;
    } BinomialNode;
    BinomialNode *root;
    int size;
    vector<BinomialNode *> ptr;

public:
    BinomialHeap(int n)
    {
        for (int i = 0; i < n; i++)
            ptr.push_back(NULL);
        root = NULL;
        size = n;
    }

    BinomialNode *unionOperation(BinomialNode *a, BinomialNode *b)
    {
        if (a || b)
        {
            BinomialNode *temp;
            if (!a)
                temp = b;
            else if (!b) 
                temp = a;
            else 
            {
                BinomialNode *tempTrail; 
                if (a->deg > b->deg)
                {
                    temp = b;
                    b = b->sibling;
                }
                else
                {
                    temp = a;
                    a = a->sibling;
                }
                tempTrail = temp;
                while (a && b)
                {
                    if (a->deg <= b->deg)
                    {
                        tempTrail->sibling = a;
                        a = a->sibling;
                    }
                    else
                    {
                        tempTrail->sibling = b;
                        b = b->sibling;
                    }
                    tempTrail = tempTrail->sibling;
                }
                if (!a)
                    tempTrail->sibling = b;
                else
                    tempTrail->sibling = a;
            }

            BinomialNode *x = NULL;
            BinomialNode *y = temp;
            BinomialNode *z = temp->sibling;
            while (z != NULL)
            {
                if (y->deg != z->deg)
                {
                    x = y;
                    y = z;
                }
                else if ((z->sibling) && (z->sibling)->deg == y->deg)
                {
                    x = y;
                    y = z;
                }
                else
                {
                    if (y->wt >= z->wt)
                    {
                        if (x == NULL)
                        {
                            temp = z;
                            z->deg = temp->deg + 1;
                        }
                        else
                        {
                            x->sibling = z;
                            z->deg = z->deg + 1;
                        }

                        y->parent = z;
                        y->sibling = z->child;
                        z->child = y;
                        y = z;
                    }
                    else // increasing deg of y
                    {
                        y->sibling = z->sibling;
                        z->parent = y;
                        z->sibling = y->child;
                        y->child = z;
                        y->deg = y->deg + 1;
                    }
                }
                z = y->sibling;
            }
            return temp;
        }
        else
            return NULL;
    }
    bool empty()
    {
        return (root == NULL);
    }

    void insertKey(int k, int wt)
    {
        BinomialNode *newNode = new (BinomialNode);
        newNode->wt = wt;
        newNode->node = k;

        newNode->child = NULL;
        newNode->deg = 0;
        newNode->parent = NULL;
        newNode->sibling = NULL;
        root = unionOperation(root, newNode);
        ptr[k] = newNode;
    }

    pair<int, int> extractMin()
    {
        BinomialNode *magic = root;
        BinomialNode *temp = root;
        BinomialNode *temp2 = NULL;
        BinomialNode *temp3 = root;

        int minW = magic->wt;
        int minV = magic->node;
        while (temp3->sibling)
        {
            if (temp3->sibling == temp3)
                break;
            if ((temp3->sibling)->wt < minW)
            {
                minW = temp3->wt;
                minV = temp3->node;
                temp2 = temp3;
                temp = temp3->sibling;
            }
            temp3 = temp3->sibling;
        }

        pair<BinomialNode *, BinomialNode *> minN = make_pair(temp2, temp);

        if (root == minN.second)
            root = minN.second->sibling;

        if (!minN.first && !((minN.second)->sibling))
            magic = NULL;
        else if (!minN.first)
            magic = minN.second->sibling;
        else
            (minN.first)->sibling = (minN.second)->sibling;

        if (minN.second->child != NULL)
        {
            BinomialNode *child = minN.second->child;
            while (child != NULL)
            {
                BinomialNode *next = child->sibling;
                child->sibling = magic;
                child->parent = NULL;
                magic = child;
                child = next;
            }
            (minN.second->child)->sibling = NULL;
        }
        else
            magic = NULL;

        pair<int, int> ans = make_pair(minN.second->wt, minN.second->node);
        BinomialNode *finalTemp = minN.second->child;
        size -= 1;
        root = unionOperation(root, magic);
        return ans;
    }
    void decreaseKey(int k, int newValue)
    {
        BinomialNode *temp2 = ptr[k];

        temp2->wt = newValue;
        BinomialNode *parent = temp2->parent;
        while (parent && (temp2->wt < parent->wt))
        {
            int cw = temp2->wt;
            int cv = temp2->node;
            int pw = parent->wt;
            int pv = parent->node;
            temp2->wt = pw;
            temp2->node = pv;
            parent->wt = cw;
            parent->node = cv;
            ptr[cv] = parent;
            ptr[pv] = temp2;
            temp2 = parent;
            parent = parent->parent;
        }
    }
};

class FibonacciHeap
{
    typedef struct unit
    {
        int wt;
        int deg;
        int node;
        bool marked;
        unit *parent, *child, *right, *left;
    } FibonacciNode;

protected:
    vector<FibonacciNode *> ptr; // to do find operation in o(1) each time
    FibonacciNode *root;
    int size;

public:
    FibonacciHeap(int n)
    {
        for (int i = 0; i < n; i++)
            ptr.push_back(NULL);
        root = NULL;
        size = n;
    }
    FibonacciNode *mergeOperation(FibonacciNode *a, FibonacciNode *b)
    {
        // no merge in case there is atleast one is null
        if (!a)
            return b;
        if (!b)
            return a;

        FibonacciNode *c = a->right;
        FibonacciNode *d = b->left;
        // interchanging a and b in case where a->wt > b->wt
        if (a->wt > b->wt)
        {
            c = b->right;
            d = a->left;
            FibonacciNode *temp = a;
            a = b;
            b = temp;
        }

        b->left = a;
        a->right = b;
        c->left = d;
        d->right = c;
        return a;
    }
    void insertKey(int k, int wt)
    {
        FibonacciNode *newNode = new FibonacciNode;
        newNode->wt = wt;
        newNode->node = k;
        newNode->deg = 0;
        newNode->marked = false;
        newNode->child = NULL;
        newNode->parent = NULL;
        newNode->right = newNode;
        newNode->left = newNode;
        ptr[k] = newNode; // to help in decrease key operation
        root = mergeOperation(root, newNode);
    }

    pair<int, int> extractMin()
    {
        FibonacciNode *temp = root;
        pair<int, int> ans = make_pair(temp->wt, temp->node);
        root = extractMinHelper(root);
        delete temp;
        return ans;
    }
    FibonacciNode *extractMinHelper(FibonacciNode *currentRoot)
    {
        size -= 1;
        FibonacciNode *temp = currentRoot->child;
        if (temp)
        {
            FibonacciNode *temp2 = temp;
            while (1) // traversing child list and setting their parents = 0
            {
                temp2->marked = 0;    // unmarking the node
                temp2->parent = NULL; // setting all their parents as zero because they have been cutOperation
                temp2 = temp2->right;
                if (temp2 == temp)
                    break;
            }
        }
        // single fibonacci tree in the system
        if (currentRoot->right == currentRoot)
            currentRoot = currentRoot->child;
        else
        {
            FibonacciNode *nLeft = currentRoot->left;
            FibonacciNode *nRight = currentRoot->right;
            nRight->left = nLeft;
            nLeft->right = nRight;
            currentRoot = mergeOperation(currentRoot->right, currentRoot->child); // here we neglect currentRoot and link currentRoot's right and currentRoot's children
        }
        // finally listing all fibo trees in the heap according to of their degs
        if (currentRoot)
        {
            vector<FibonacciNode *> trees; // I am assuming a threshold of 2^127 nodes.
            for (int i = 0; i < 128; i++)
                trees.push_back(NULL);
            while (1)
            {
                FibonacciNode *test = trees[currentRoot->deg];
                if (test == currentRoot)
                    break;
                if (test) // if there is a fibonacci tree of given deg present in the heap
                {
                    trees[currentRoot->deg] = NULL;
                    FibonacciNode *testL = test->left;
                    testL->right = test->right;
                    test->right->left = test->left;

                    // to make test as a child of currentRoot
                    if (currentRoot->wt < test->wt)
                    {
                        test->left = test;
                        test->right = test;
                        test->parent = currentRoot;
                        currentRoot->deg = currentRoot->deg + 1;
                        currentRoot->child = mergeOperation(currentRoot->child, test);
                    }

                    else
                    {
                        if (currentRoot->right != currentRoot)
                        {
                            FibonacciNode *cL = currentRoot->left;
                            FibonacciNode *cR = currentRoot->right;

                            cL->right = test;
                            cR->left = test;
                            test->right = cR;
                            test->left = cL;
                        }

                        else // single tree case
                        {
                            test->right = test;
                            test->left = test;
                        }
                        currentRoot->left = currentRoot; // creating linked list of one element here
                        currentRoot->right = currentRoot;
                        currentRoot->parent = test;
                        test->deg = test->deg + 1;
                        test->child = mergeOperation(test->child, currentRoot);
                        currentRoot = test;
                    }
                    currentRoot = currentRoot->right; // to move to next part
                }
                else
                {
                    trees[currentRoot->deg] = currentRoot;
                    currentRoot = currentRoot->right;
                }
            }
            FibonacciNode *min = currentRoot;
            // setting new min element after removing previous min
            while (1)
            {
                if (currentRoot->wt < min->wt)
                    min = currentRoot;
                currentRoot = currentRoot->right;
                if (currentRoot == min)
                    break;
            }
            return min;
        }
        return NULL;
    }
    FibonacciNode *cutOperation(FibonacciNode *a, FibonacciNode *b) // serves the cut operation of fibo heap
    {
        FibonacciNode *bLeft = b->left;
        FibonacciNode *bRight = b->right;
        FibonacciNode *bParent = b->parent;

        // single fibTree case
        if (b->right == b)
            bParent->child = NULL;
        else
        {
            bRight->left = bLeft;
            bLeft->right = bRight;
            bParent->child = bRight;
        }
        b->right = b;
        b->left = b;
        b->marked = 0;
        bParent->deg = bParent->deg - 1; // reducing the deg by 1
        return mergeOperation(a, b);
    }
    void cascadingCutOperation(FibonacciNode *parent, FibonacciNode *found) // serves cascading cut functionality
    {
        while (parent)
        {
            if (parent->marked == false)
                break;
            root = cutOperation(root, parent);
            found = parent;
            parent = found->parent;
            found->parent = NULL; // making the parent null
        }
        if (parent && parent->parent && parent->marked == false)
            parent->marked = true; // unmarked node will be marked
    }
    void decreaseKey(int k, int newValue)
    {
        // find the FibonacciNode first
        FibonacciNode *temp = root;
        FibonacciNode *found = ptr[k]; // using pre stored pointer locations

        found->wt = newValue; // setting new value
        FibonacciNode *parent = found->parent;
        if (parent && found->wt < parent->wt)
        {
            root = cutOperation(root, found);
            found->parent = NULL;
            cascadingCutOperation(parent, found);
            // setting min
            if (found->wt < root->wt)
                root = found;
        }
        if (root) // this piece of code resets the min pointer to avoid any seg fault just in case
        {
            FibonacciNode *temp2 = root;
            while (1)
            {
                if (temp2->wt < root->wt)
                    root = temp2;
                temp2 = temp2->right;
                if (temp2 == root)
                    break;
            }
        }
    }

    bool empty()
    {
        return root == NULL;
    }
};

class ArrayHeap
{
    int *harr;
    int cap;
    int size;

public:
    ArrayHeap(int c)
    {
        size = 0;
        cap = c;
        harr = new int[cap];
        for (int i = 0; i < cap;i++)
            harr[i] = INF;
    }

    void insertKey(int k, int wt)
    {
        harr[k] = wt;
        size++;
    }

    pair<int, int> extractMin()
    {
        int minElement = INF;
        int minIndex = 0;
        for (int i = 0; i < cap; i++) // to find minValue
        {
            if (harr[i] < minElement)
            {
                minElement = harr[i];
                minIndex = i;
            }
        }
        size--;
        harr[minIndex] = INF; // setting it to be inf so that it couldn't be found again
        return make_pair(minElement, minIndex);
    }

    void decreaseKey(int v, int newValue)
    {
        harr[v] = newValue;
    }

    bool empty()
    {
        if(size == 0) {
            for (int i = 0; i < cap;i++)
                harr[i] = INF;
        }
        return (size == 0);
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

vector<vector<int>> Dijkstra(int V, vector<pair<int, int>> adj[], set<int> cycle, int heap_type)
{
    vector<vector<int>> dist(V, vector<int>(V, INF));
    if(heap_type == 4) {
        // cout << "Fibonacci" << endl;
        FibonacciHeap q = FibonacciHeap(V);
        for (int i = 0; i < V; i++)
        {
            int src = i;
            if (cycle.find(src) != cycle.end())
            {
                continue;
            }
            for (int j = 0; j < V; j++)
            {
                if (j == src)
                    q.insertKey(src, 0);
                else
                    q.insertKey(j, INF);
            }
            dist[i][i] = 0;

            while (!q.empty())
            {
                pair<int, int> p = q.extractMin();
                int node = p.second;
                int currDist = p.first;
                if (dist[i][node] < currDist)
                    continue;
                for (auto x : adj[node])
                {
                    int ver = x.first;
                    int wt = x.second;
                    if (cycle.find(ver) == cycle.end() && wt + dist[i][node] < dist[i][ver])
                    {
                        dist[i][ver] = wt + dist[i][node];
                        q.decreaseKey(ver, dist[i][ver]);
                    }
                }
            }
        }
        return dist;
    }
    else if(heap_type == 3){
        // cout << "Binomial" << endl;
        BinomialHeap q = BinomialHeap(V);
        for (int i = 0; i < V; i++)
        {
            int src = i;
            if (cycle.find(src) != cycle.end())
            {
                continue;
            }
            for (int j = 0; j < V; j++)
            {
                if (j == src)
                    q.insertKey(src, 0);
                else
                    q.insertKey(j, INF);
            }
            dist[i][i] = 0;

            while (!q.empty())
            {
                pair<int, int> p = q.extractMin();
                int node = p.second;
                int currDist = p.first;
                if (dist[i][node] < currDist)
                    continue;
                for (auto x : adj[node])
                {
                    int ver = x.first;
                    int wt = x.second;
                    if (cycle.find(ver) == cycle.end() && wt + dist[i][node] < dist[i][ver])
                    {
                        dist[i][ver] = wt + dist[i][node];
                        q.decreaseKey(ver, dist[i][ver]);
                    }
                }
            }
        }
        return dist;
    } 
    else if(heap_type == 2){
        // cout << "Binary" << endl;
        BinaryHeap q = BinaryHeap(V);
        for (int i = 0; i < V; i++)
        {
            int src = i;
            if (cycle.find(src) != cycle.end())
            {
                continue;
            }
            for (int j = 0; j < V; j++)
            {
                if (j == src)
                    q.insertKey(src, 0);
                else
                    q.insertKey(j, INF);
            }
            dist[i][i] = 0;

            while (!q.empty())
            {
                pair<int, int> p = q.extractMin();
                int node = p.second;
                int currDist = p.first;
                if (dist[i][node] < currDist)
                    continue;
                for (auto x : adj[node])
                {
                    int ver = x.first;
                    int wt = x.second;
                    if (cycle.find(ver) == cycle.end() && wt + dist[i][node] < dist[i][ver])
                    {
                        dist[i][ver] = wt + dist[i][node];
                        q.decreaseKey(ver, dist[i][ver]);
                    }
                }
            }
        }
        return dist;
    }
    else if(heap_type == 1){
        // cout << "Array" << endl;
        ArrayHeap q = ArrayHeap(V);
        for (int i = 0; i < V; i++)
        {
            int src = i;
            if (cycle.find(src) != cycle.end())
            {
                continue;
            }
            for (int j = 0; j < V; j++)
            {
                if (j == src)
                    q.insertKey(src, 0);
                else
                    q.insertKey(j, INF);
            }
            dist[i][i] = 0;

            while (!q.empty())
            {
                pair<int, int> p = q.extractMin();
                int node = p.second;
                int currDist = p.first;
                if (dist[i][node] < currDist)
                    continue;
                for (auto x : adj[node])
                {
                    int ver = x.first;
                    int wt = x.second;
                    if (cycle.find(ver) == cycle.end() && wt + dist[i][node] < dist[i][ver])
                    {
                        dist[i][ver] = wt + dist[i][node];
                        q.decreaseKey(ver, dist[i][ver]);
                    }
                }
            }
        }
        return dist;
    }
    else{
        FibonacciHeap q = FibonacciHeap(V);
        for (int i = 0; i < V; i++)
        {
            int src = i;
            if (cycle.find(src) != cycle.end())
            {
                continue;
            }
            for (int j = 0; j < V; j++)
            {
                if (j == src)
                    q.insertKey(src, 0);
                else
                    q.insertKey(j, INF);
            }
            dist[i][i] = 0;

            while (!q.empty())
            {
                pair<int, int> p = q.extractMin();
                int node = p.second;
                int currDist = p.first;
                if (dist[i][node] < currDist)
                    continue;
                for (auto x : adj[node])
                {
                    int ver = x.first;
                    int wt = x.second;
                    if (cycle.find(ver) == cycle.end() && wt + dist[i][node] < dist[i][ver])
                    {
                        dist[i][ver] = wt + dist[i][node];
                        q.decreaseKey(ver, dist[i][ver]);
                    }
                }
            }
        }
        return dist;
    }
}

void Johnson(int V, vector<pair<int, int>> adj[], int heap_type)
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

    vector<vector<int>> SP = Dijkstra(V, adj, cycle, heap_type);

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

int main(int argc, char *argv[])
{
    int T;
    cin >> T;
    int heap_type = stoi(argv[1]);
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
        Johnson(N, adj, heap_type);
        end = clock();
        time = (double) (end - start) / 1000;
        time_taken.push_back(time);
    }
    for (double i : time_taken)
        cout << (double) i << " ";
    cout << endl;
}
#include<bits/stdc++.h>
using namespace std;

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

    node* new_node(pair<int,int> p){
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
    void Insert(pair<int,int> p)
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
        else minptr = temp;
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
    pair<int,int> Extract_min()
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

    void display()
    {
        node *ptr = minptr;
        if (ptr == NULL)
            cout << "The Heap is Empty" << endl;

        else
        {
            cout << "The root nodes of Heap are: " << endl;
            do
            {
                cout << ptr->val;
                ptr = ptr->right;
                if (ptr != minptr)
                {
                    cout << "-->";
                }
            } while (ptr != minptr && ptr->right != NULL);
            cout << endl
                 << "The heap has " << num << " nodes" << endl
                 << endl;
        }
    }
};


int main(){

    Fibonacci_Heap obj = Fibonacci_Heap();

    cout << "Creating an initial heap" << endl;
    obj.Insert({5,0});
    obj.Insert({2,0});
    obj.Insert({8,0});

    obj.display();

    cout << "Extracting min" << endl;
    obj.Extract_min();
    obj.display();
    
    cout << "Extracting min" << endl;
    obj.Extract_min();
    obj.display();
}
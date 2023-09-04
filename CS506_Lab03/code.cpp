#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


int max(int a, int b){
    return (a > b) ? a : b;
}

int min(int a, int b){
    return (a < b) ? a : b;
}

struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
};

struct Node* newnode(int val, int ht, struct Node* lt, struct Node* rt){
    struct Node *tem = (struct Node *)malloc(sizeof(struct Node));
    tem->data = val;
    tem->height = ht;
    tem->left = NULL;
    tem->right = NULL;
}

int Height(struct Node* root){
    if(root == NULL)
        return -1;
    return root->height;
}

int Height_Diff(struct Node* root){
    if(root == NULL)
        return 0;
    return Height(root->left) - Height(root->right);
} 

struct Node* minclosenode(struct Node* root){
    struct Node *temp = root;
    while(temp->right != NULL){
        temp = temp -> right;
    }
    return temp;
}

struct Node* LLRotation(struct Node* root){
    // printf("LL Rotation\n");
    struct Node *z = root, *y = root->left, *x = root->left->left;
    struct Node *T1 = y->right;
    z->left = T1;
    y->right = z;
    z->height = max(Height(z->left), Height(z->right)) + 1;
    y->height = max(Height(y->left), Height(y->right)) + 1;
    return y;
}

struct Node* LRRotation(struct Node* root){
    // printf("LR Rotation\n");
    struct Node *z = root, *y = root->left, *x = root->left->right;
    struct Node *T1 = x->left, *T2 = x->right;
    y->right = T1;
    z->left = T2;
    x->left = y;
    x->right = z;
    y->height = max(Height(y->left), Height(y->right)) + 1;
    z->height = max(Height(z->left), Height(z->right)) + 1;
    x->height = max(Height(x->left), Height(x->right)) + 1;
    return x;
}

struct Node* RRRotation(struct Node* root){
    // printf("RR Rotation\n");
    struct Node *z = root, *y = root->right, *x = root->right->right;
    struct Node *T1 = y->left;
    z->right = T1;
    y->left = z;
    z->height = max(Height(z->left), Height(z->right)) + 1;
    y->height = max(Height(y->left), Height(y->right)) + 1;
    return y;
}

struct Node* RLRotation(struct Node* root){
    // printf("RL Rotation\n");
    struct Node *z = root, *y = root->right, *x = root->right->left;
    struct Node *T1 = x->left, *T2 = x->right;
    z->right = T1;
    y->left = T2;
    x->left = z;
    x->right = y;
    y->height = max(Height(y->left), Height(y->right)) + 1;
    z->height = max(Height(z->left), Height(z->right)) + 1;
    x->height = max(Height(x->left), Height(x->right)) + 1;
    return x;
}

struct Node* Insert(struct Node* root, int val, bool isAVL){
    if(root == NULL)
        return newnode(val, 0, NULL, NULL);
    if(root->data == val)
        return root;
    if(val < root->data)
        root->left = Insert(root->left, val, isAVL);
    if(val > root->data)
        root->right = Insert(root->right, val, isAVL);
    root->height = max(Height(root->left), Height(root->right)) + 1;
    if(isAVL){
        int hd = Height_Diff(root);
        if(hd > 1 && val > root->left->data)
            root = LRRotation(root);
        else if(hd < -1 && val < root->right->data)
            root = RLRotation(root);
        else if(hd > 1 && val < root->left->data)
            root = LLRotation(root);
        else if(hd < -1 && val > root->right->data)
            root = RRRotation(root);
    }
    return root;
}

struct Node* Delete(struct Node* root, int val, bool isAVL){
    if(root == NULL)
        return NULL;
    // printf("In delete I'm checking %d for %d\n", root->data, val);
    if(root->data > val)
        root->left = Delete(root->left, val, isAVL);
    if(root->data < val)
        root->right = Delete(root->right, val, isAVL);
    if(root->data == val){
        // printf("found\n");
        if(root->left == NULL || root->right == NULL){
            struct Node *temp = root;
            if(root->left != NULL)
                root = root->left;
            else
                root = root->right;
            free(temp);
        }
        else{
            struct Node *temp = minclosenode(root->left);
            root->data = temp->data;
            root->left = Delete(root->left, temp->data, isAVL);
        }
    }
    if(root == NULL)
        return root;
    root->height = max(Height(root->left), Height(root->right)) + 1;
    if(isAVL){
        int hd = Height_Diff(root);
        if(hd > 1 && Height_Diff(root->left) >= 0)
            root = LLRotation(root);
        else if(hd > 1 && Height_Diff(root->left) < 0)
            root = LRRotation(root);
        else if(hd < -1 && Height_Diff(root->right) >= 0)
            root = RLRotation(root);
        else if(hd < -1 && Height_Diff(root->right) < 0)
            return RRRotation(root);
    }
    return root;
}

struct Node* Search(struct Node* root, int val){
    if(root == NULL)
        return NULL;
    if(val == root->data)
        return root;
    if(val > root->data)
        return Search(root->right, val);
    if(val < root->data)
        return Search(root->left, val);
}

void Count(struct Node* root, int &nodes, int &leaves){
    if(root == NULL)
        return;
    if(root->left == NULL && root->right == NULL)
        leaves++;
    nodes++;
    Count(root->left, nodes, leaves);
    Count(root->right, nodes, leaves);
}

struct List{
    int val;
    struct List *next;
};

void Print(struct List* head)
{
    struct List *temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

struct List* newlistnode(int value, List* nex){
    struct List *temp = (struct List *)malloc(sizeof(List));
    temp->next = nex;
    temp->val = value;
    return temp;
}

struct List *ReverseList(struct List *head)
{
    struct List *prev = NULL, *cur = head;
    while (cur != NULL)
    {
        struct List *temp = cur;
        cur = cur->next;
        temp->next = prev;
        prev = temp;
    }
    head = prev;
    return prev;
}

bool FindNode(struct Node *root, int value){
    if(Search(root, value) != NULL)
        return true;
    return false;
}

int LCA(struct Node* root, int i, int j){
    // printf("finding LCA of i = %d & j = %d and having root->data = %d\n", i, j, root->data);
    if(!FindNode(root, i) || !FindNode(root, j))
        return -1;
    if(i<=root->data && j>=root->data)
        return root->data;
    if(j<root->data)
        return LCA(root->left, i, j);
    return LCA(root->right, i, j);
}

char* GetPath(struct Node* root, int j){
    char *ans;
    sprintf(ans, "%d", root->data);
    if(root->data == j)
        return ans;
    if(j > root->data){
        strcat(ans, " R ");
        strcat(ans, GetPath(root->right, j));
    }
    else {
        strcat(ans, " L ");
        strcat(ans, GetPath(root->left, j));
    }
    return ans;
}

char* PrintRoute(struct Node* root, int i, int j){
    struct Node *anc = Search(root, i);
    struct Node *des = Search(root, j);
    char *c;
    if(anc == NULL)
        c = "Source does not exist";
    return c;
    if(des == NULL)
        return c = "Destination does not exist";
    if(!FindNode(anc, des->data))
        return c = "Unreachable";
    return GetPath(root, j);
}

int NumLeaves(struct Node* root){
    int leaves = 0, nodes = 0;
    Count(root, nodes, leaves);
    return leaves;
}

int NumNodes(struct Node* root){
    int leaves = 0, nodes = 0;
    Count(root, nodes, leaves);
    return nodes;
}

struct NodeList{
    Node *node;
    NodeList *next;
};

struct NodeList* newNodeList(struct Node* node, struct NodeList* nxt){
    struct NodeList* temp = (struct NodeList *)malloc(sizeof(NodeList));
    temp->next = nxt;
    temp->node = node;
    return temp;
}

void PreOrder(struct Node* root){
    NodeList *st = NULL;
    if(root != NULL)
        st = newNodeList(root, st);
    while(st != NULL){
        struct Node *temp = st->node;
        printf("%d ", temp->data);
        struct NodeList *t = st;
        st = st->next;
        free(t);
        if(temp->right != NULL)
            st = newNodeList(temp->right, st);
        if(temp->left != NULL)
            st = newNodeList(temp->left, st);
    }  
}

void InOrder(struct Node* root){
    if(root == NULL)
        return;
    InOrder(root->left);
    printf("%d ", root->data);
    InOrder(root->right);
}

void PostOrder(struct Node* root){
    if (root == NULL)
        return;
    PostOrder(root->left);
    PostOrder(root->right);
    printf("%d ", root->data);
}

void LevelOrder(struct Node* root){
    struct NodeList *st = NULL, *end = NULL;
    if(root == NULL)
        return;
    st = newNodeList(root, NULL);
    end = st;
    while(st != NULL){
        struct NodeList *temp = st;
        struct Node *tem = temp->node;
        printf("%d ", tem->data);
        if(tem->left != NULL) {
            end->next = newNodeList(tem->left, NULL);
            end = end->next;
        }
        if(tem->right != NULL) {
            end->next = newNodeList(tem->right, NULL);
            end = end->next;
        }
        st = st->next;
        free(temp);
    }
}

void SpecialTrav(struct Node* root, int i, int *arr){
    if(root == NULL)
        return;
    arr[i]++;
    SpecialTrav(root->left, i + 1, arr);
    SpecialTrav(root->right, i + 1, arr);
}

int Width(struct Node* root){
    int n = Height(root) + 1;
    int arr[n] = {0};
    SpecialTrav(root, 0, arr);
    int ans = 0;
    for (int i = 0; i < n;i++){
        ans = max(ans, arr[i]);
    }
    return ans;
}

void DiameterTrav(struct Node* root, int &ans){
    if(root == NULL)
        return;
    ans = max(ans, Height(root->left) + Height(root->right) + 3);
    // printf("rootval = %d  and Height(left) = %d and Height(right) = %d ans = %d\n", root->data, Height(root->left), Height(root->right), ans);
    DiameterTrav(root->left, ans);
    DiameterTrav(root->right, ans);
}

int Diameter(struct Node* root){
    int ans = 0;
    DiameterTrav(root, ans);
    return ans;
}

int LeftSum(struct Node* root){
    int ans = 0;
    while(root != NULL){
        if(root->left == NULL && root->right == NULL)
            break;
        ans += root->data;
        root = root->left;
    }
    return ans;
}

int RightSum(struct Node* root){
    int ans = 0;
    while(root != NULL){
        if(root->left == NULL && root->right == NULL)
            break;
        ans += root->data;
        root = root->right;
    }
    return ans;
}

int LeafSum(struct Node* root){
    if(root == NULL)
        return 0;
    if(root->left == NULL && root->right == NULL)
        return root->data;
    int ans = LeafSum(root->left) + LeafSum(root->right);
    return ans;
}

void FindLeaves(struct Node* root, struct List* &ans){
    if(root == NULL)
        return;
    if(root->left == NULL && root->right == NULL)
        ans = newlistnode(root->data, ans);
    FindLeaves(root->right, ans);
    FindLeaves(root->left, ans);
}

void BoundaryTrav(struct Node* root){
    struct List *ans = NULL;
    struct Node *temp = root;
    while(temp!=NULL){
        if(temp->left == NULL && temp->right == NULL)
            break;
        ans = newlistnode(temp->data, ans);
        temp = temp->right;
    }
    temp = root;
    FindLeaves(temp, ans);
    temp = root;
    struct List *lefts = NULL;
    while(temp != NULL){
        if(temp->left == NULL && temp->right == NULL)
            break;
        if(temp != root)
            lefts = newlistnode(temp->data, lefts);
        temp = temp->left;
    }
    lefts = ReverseList(lefts);
    for (struct List *i = lefts; i != NULL;i=i->next){
        ans = newlistnode(i->val, ans);
    }
    ans = ReverseList(ans);
    Print(ans);
}

void Perimeter(struct Node* root){
    if(root == NULL)
        return;
    int ans = RightSum(root) + LeftSum(root) + LeafSum(root) - root->data;
    printf("%d ", ans);
    BoundaryTrav(root);
}

void ClearTree(struct Node* root){
    if(root == NULL)
        return;
    ClearTree(root->left);
    ClearTree(root->right);
    free(root);
}

int main()
{
    int test;
    scanf("%d\n", &test);
    struct Node *root = NULL;
    bool isAVL = true;
    for (int i = 0; i < test;i++){
        char c, e;
        scanf("%c%c", &c, &e);
        // printf("%c\n", c);
        if(c == 'T' || c == 'H' || c == 'A' || c == 'U'){
            struct List *arr = NULL;
            while (true)
            {
                char temp;
                int value;
                scanf("%d%c", &value, &temp);
                struct List *tempnode = newlistnode(value, arr);
                arr = tempnode;
                if (temp == '\n')
                    break;
            }
            arr = ReverseList(arr);
            // Print(arr);
            struct List *temp = arr;
            if (c == 'T' || c == 'H'){
                ClearTree(root);
                root = NULL;
                if (c == 'T')
                    isAVL = false;
                if (c == 'H')
                    isAVL = true;
                // printf("Good\n");
                while(temp != NULL){
                    if(temp->val > 0)
                        root = Insert(root, temp->val, isAVL);
                    if(temp->val < 0)
                        root = Delete(root, -temp->val, isAVL);
                    temp = temp->next;
                    // PreOrder(root);
                    // printf("\n");
                }
            }
            else{
                if(c == 'A'){
                    while(temp != NULL){
                        if(temp->val > 0)
                            root = Insert(root, temp->val, isAVL);
                        temp = temp->next;
                    }
                }
                else{
                    while(temp != NULL){
                        if(temp->val > 0)
                            root = Delete(root, temp->val, isAVL);
                        temp = temp->next;
                    }
                }
            }
        }
        else if(c == 'F') {
            int x;
            scanf("%d%c", &x);
            FindNode(root, x);
        }
        else if(c == 'C' || c == 'R') {
            int a, b;
            scanf("%d %d%c", &a, &b);
            if(c == 'C')
                printf("%d\n", LCA(root, min(a,b), max(a,b)));
            else
                printf("%s\n", PrintRoute(root, a, b));
        }
        else {
            if(c == 'Q')
                printf("%d\n", NumLeaves(root));
            if(c == 'N')
               printf("%d\n", NumNodes(root));
            if(c == 'P'){
                PreOrder(root);
                printf("\n");
            }
            if (c == 'I'){
                InOrder(root);
                printf("\n");
            }
            if(c == 'S'){
                PostOrder(root);
                printf("\n");
            }
            if(c == 'L'){
                LevelOrder(root);
                printf("\n");
            }
            if(c == 'D')
                printf("%d\n", Height(root));
            if(c == 'W')
                printf("%d\n", Width(root));
            if(c == 'X')
                printf("%d\n", Diameter(root));
            if(c == 'Y')
                Perimeter(root);
        }
        
    }
    return 0;
}
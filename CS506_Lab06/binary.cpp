#include<bits/stdc++.h>
using namespace std;

class Binary_Heap{
    private:
    struct Node{
        int val, nd;
        struct Node *left, *right, *parent;
    };

    Node *root = NULL;
    int size = 0;

    Node* new_node(pair<int,int> p, Node* par){
        Node *node = new Node();
        node->val = p.first;
        node->nd = p.second;
        node->left = NULL;
        node->right = NULL;
        node->parent = par;
    }

    Node* insert_helper(pair<int,int> p, int size){
        if(size == 1)
            return new_node(p, NULL);
        else
            return insert_helper(p, size / 2);
    }

    public:

    void Insert(pair<int,int> p){

    }
};

int main(){
    return 0;
}
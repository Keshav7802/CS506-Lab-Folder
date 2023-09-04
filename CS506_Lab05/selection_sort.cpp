#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    struct Node *next;
};

void Print(Node *head)
{
    for (Node *temp = head; temp != NULL; temp = temp->next)
    {
        cout << temp->data << " ";
    }
    cout << endl;
}

Node* Find_Min(Node* &head){
    Node *bef_min = head;
    for (Node *temp = head; temp != NULL; temp = temp->next){
        struct Node *t = temp->next;
        if(t == NULL)
            break;
        if(t->data < bef_min->next->data) {
            bef_min = temp;
        }
    }
    // cout << "bef_min = " << bef_min->data<< endl;
    Node *ans = NULL;
    if(bef_min == head) {
        if(bef_min->next == NULL || bef_min->next->data > bef_min->data)
            ans = bef_min;
        else
            ans = bef_min->next;
    }
    else
        ans = bef_min->next;
    // cout << "ans = " << ans->data << endl;
    if(ans == head)
        head = head->next;
    else
        bef_min->next = ans->next;
    ans->next = NULL;
    // cout << "head = ";
    // Print(head);
    // cout << "ans = ";
    // Print(ans);
    return ans;
}

Node *new_node(int val, Node *nxt)
{
    Node *ans = (Node *) malloc(sizeof(Node));
    ans->data = val;
    ans->next = nxt;
    return ans;
}

Node* Insert(Node* head, Node* node){
    node->next = head;
    return node;
}

void Selection_Sort(Node* &head){
    Node *temp = head;
    head = NULL;
    while(temp != NULL){
        // cout << "temp" << endl;
        // Print(temp);
        Node *min = Find_Min(temp);
        head = Insert(head, min);
        // cout << "head" << endl;
        // Print(head);
    }
}


int main(){
    int arr[] = {9, 8, 7, 6, 5, 4, 3, 2};
    int n = 8;
    Node *list = NULL;
    for (int i = 0; i < n;i++){
        list = new_node(arr[i], list);
    }
    Print(list);
    Selection_Sort(list);
    Print(list);
    return 0;
}
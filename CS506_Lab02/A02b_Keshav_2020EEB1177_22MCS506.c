/*
This Code works well for 110 if we find just find it once because for N = 110 the the no of nodes
in the list becomes 1e5 and we need to multiply it 110 times more with 110 then the time complexity
already reaches 1e7.

One Optimal Solution we can do is that if we store the i^i for each i in separate place and also we store
# value of J from 1 to N (max to which is asked) then from N+1 to N' we can calculate but that will also involve
1e5 * 1e2 (in worst case) and in practice when implemented it is not working even for N < 110.
Hence submitting this solution.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *newNode(int val, struct Node *nxt)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = val;
    node->next = nxt;
    return node;
}

void Print(struct Node *head)
{
    for (struct Node *temp = head; temp != NULL; temp = temp->next)
    {
        printf("%d", temp->data);
    }
    printf("\n");
}

int Size(struct Node* head) {
    int ans = 0;
    for (struct Node *temp = head; temp != NULL; temp = temp->next){
        ans++;
    }
    return ans;
}

struct Node* ReverseList(struct Node* head){
    struct Node *prev = NULL, *cur = head;
    while(cur != NULL){
        struct Node *temp = cur;
        cur = cur->next;
        temp->next = prev;
        prev = temp;
    }
    head = prev;
    return prev;
}


struct Node* Add(struct Node* A, struct Node* B){
    struct Node *ans = NULL;
    int carr = 0;
    int i = 0;
    while(A!=NULL || B!=NULL){
        int a = 0, b = 0;
        if(A != NULL)
            a = A->data;
        if(B != NULL)
            b = B->data;
        int c = a + b + carr;
        ans = newNode(c % 10, ans);
        carr = c / 10;
        if(A != NULL) A = A->next;
        if(B != NULL) B = B->next;
    }
    if(carr)
        ans = newNode(carr, ans);
    ans = ReverseList(ans);
    return ans;
}

struct Node* Multiply(struct Node* head, int num){
    struct Node *ans = newNode(0, NULL);
    int co = 0;
    while(num){
        int a = num % 10;
        num /= 10;
        int carr = 0;
        struct Node *newlist = NULL;
        for (int i = 0; i < co;i++)
            newlist = newNode(0, newlist);
        for (struct Node *temp = head; temp != NULL; temp = temp->next)
        {
            int b = temp->data;
            int c = a * b + carr;
            newlist = newNode(c % 10, newlist);
            carr = c / 10;
        }
        if(carr)
            newlist = newNode(carr, newlist);
        newlist = ReverseList(newlist);
        ans = Add(ans, newlist);
        co++;
    }
    return ans;
}

struct Node *ListMultiply(struct Node *head, struct Node* num)
{
    struct Node *ans = newNode(0, NULL);
    int co = 0;
    while (num != NULL)
    {
        int a = num->data % 10;
        num = num->next;
        int carr = 0;
        struct Node *newlist = NULL;
        for (int i = 0; i < co; i++)
            newlist = newNode(0, newlist);
        for (struct Node *temp = head; temp != NULL; temp = temp->next)
        {
            int b = temp->data;
            int c = a * b + carr;
            newlist = newNode(c % 10, newlist);
            carr = c / 10;
        }
        if (carr)
            newlist = newNode(carr, newlist);
        newlist = ReverseList(newlist);
        ans = Add(ans, newlist);
        co++;
    }
    return ans;
}

int main()
{

    int T;
    scanf("%d", &T);
    while(T--){
        int N, K = 0, s = 0;
        char str[1000];
        scanf("%d %s", &N, &str);
        for (int i = 0; i < 1000;i++){
            if(str[i] >= '0' && str[i] <= '9'){
                K = K * 10 + str[i] - '0';
                s++;
            }
            else
                break;
        }
        struct Node *head = newNode(1, NULL);
        for (int i = 1; i <= N;i++){
            struct Node *pw = newNode(1, NULL);
            for (int j = 0; j < i;j++){
                pw = Multiply(pw, i);
            }
            head = ListMultiply(head, pw);
        }
        int zeroes = 0;
        for (struct Node *temp = head; temp != NULL; temp = temp->next){
            if(temp->data)
                break;
            else
                zeroes++;
        }
        int patterncount = 0, t = K;
        head = ReverseList(head);
        for (struct Node *temp = head; temp != NULL; temp = temp -> next){
            int num = 0;
            int j = 0;
            for (struct Node *tem = temp; tem != NULL; tem = tem->next){
                if(j==s)
                    break;
                num = num * 10 + tem->data;
                j++;
            }
            if(num == K)
                patterncount++;
        }
        // printf("size = %d\n", Size(head));
        printf("%d %d ", zeroes, patterncount);
        Print(head);
    }
}

/*
6
3 1
5 7
9 941
9 09
7 3
9 22
*/

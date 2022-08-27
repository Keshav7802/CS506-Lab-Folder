#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
    int data;
    struct Node *next;
};

int size = 0;
struct Node *head, *last;

struct Node *newNode(int val, struct Node *nxt)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = val;
    node->next = nxt;
    return node;
}

void FrontInsert(int val)
{
    struct Node *temp = newNode(val, head);
    if (head == NULL)
        last = temp;
    head = temp;
    size++;
}

void RearInsert(int val)
{
    struct Node *temp = newNode(val, NULL);
    if (last == NULL)
    {
        head = temp;
        last = temp;
    }
    else
    {
        last->next = temp;
        last = temp;
    }
    size++;
}

void FrontDelete()
{
    if (head == NULL)
    {
        printf("E ");
        return;
    }
    struct Node *temp = head;
    head = head->next;
    if (head == NULL)
        last = NULL;
    free(temp);
    size--;
}

void RearDelete()
{
    if (last == NULL)
    {
        printf("E ");
        return;
    }
    struct Node *st = head;
    if (st == last)
    {
        if (last != NULL)
            free(last);
        size--;
        st = NULL;
        last = NULL;
        head = NULL;
        return;
    }
    while (st->next != last)
    {
        st = st->next;
    }
    free(last);
    st->next = NULL;
    last = st;
    size--;
}

void DeleteNode(int val)
{
    struct Node *temp = head, *prev = NULL;
    while (temp != NULL)
    {
        if (temp->data == val)
            break;
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("N ");
        return;
    }
    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;
    free(temp);
    size--;
}

void FindNode(int val)
{
    struct Node *temp = head;
    int i = 1;
    while (temp != NULL)
    {
        if (temp->data == val)
        {
            printf("%d(%d) ",i ,temp - head);
            return;
        }
        i++;
        temp = temp->next;
    }
    printf("N ");
}

void Print()
{
    struct Node *temp = head;
    if(temp == NULL){
        printf("E ");
        return;
    }
    printf("[");
    while (temp != NULL)
    {
            printf("%d", temp->data);
        if(temp->next != NULL)
            printf("-");
        temp = temp->next;
    }
    printf("] ");
}


int main()
{
    int T;
    scanf("%d", &T);
    int k = 1;
    while(k<=T){
        while(size>0){
            RearDelete();
        }
        int N;
        scanf("%d", &N);
        printf("#%d ", k++);
        for (int i = 0; i < N; i++)
        {
            int a;
            scanf("%d", &a);
            if (a == 3 || a == 4 || a == 7 || a == 8)
            {
                if (a == 3)
                    FrontDelete();
                if (a == 4)
                    RearDelete();
                if (a == 7)
                    printf("%d ", size);
                if (a == 8)
                    Print();
            }
            else
            {
                if(a<1 || a>8){
                    printf("W ");
                    continue;
                }
                int b;
                scanf("%d", &b);
                if (a == 1)
                    FrontInsert(b);
                if (a == 2)
                    RearInsert(b);
                if (a == 5)
                    DeleteNode(b);
                if (a == 6)
                    FindNode(b);
            }
        }
        printf("\n");
    }
}
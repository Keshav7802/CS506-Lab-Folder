#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    int data;
    struct Node *next;
};

int size = 0;
struct Node *head, *last;

struct Node *newNode(int val, struct Node* nxt){
    struct Node* node = (struct Node *)malloc(sizeof(struct Node));
    node->data = val;
    node->next = nxt;
    return node;
}
void FrontInsert(int val){
    struct Node *temp = newNode(val, head);
    if(head == NULL)
        last = temp;
    head = temp;
    size++;
}

void RearInsert(int val){
    struct Node *temp = newNode(val, NULL);
    if(last == NULL){
        head = temp;
        last = temp;
    }
    else{
        last->next = temp;
        last = temp;
    }
    size++;
}

void FrontDelete(){
    if(head == NULL){
        printf("Cannot Delete as NO Node in the linked-list\n");
        return;
    }
    struct Node *temp = head;
    head = head->next;
    if(head == NULL)
        last = NULL;
    free(temp);
    size--;
}

void RearDelete(){
    if(last == NULL){
        printf("Cannot Delete as NO Node in the linked-list\n");
        return;
    }
    struct Node *st = head;
    if(st == last){
        if(last != NULL)
            free(last);
        st = NULL;
        last = NULL;
        return;
    }
    while(st->next != last){
        st = st->next;
    }
    free(last);
    st->next = NULL;
    last = st;
    size--;
}

void DeleteNode(int val){
    struct Node *temp = head, *prev = NULL;
    while(temp != NULL){
        if(temp->data == val)
            break;
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Cannot delete as no such node in the linked-list\n");
        return;
    }
    if(prev == NULL) 
        head = temp->next;
    else
        prev->next = temp->next;
    free(temp);
    size--;
}

void FindNode(int val){
    struct Node *temp = head;
    while(temp != NULL){
        if(temp->data == val){
            printf("%d\n", temp - head);
            return;
        }
    }
    printf("Cannot find any such node in the linked-list\n");
}

void Print(){
    struct Node *temp = head;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(){
    while(true){
        int choice;
        scanf("%d", &choice);
        if(choice == 0)
            break;
        if(choice < 0 || choice > 8){
            printf("Wrong Input\n");
            continue;
        }
        if(choice == 3){
            FrontDelete();
            continue;
        }
        if(choice == 4){
            RearDelete();
            continue;
        }
        if(choice == 7){
            printf("%d\n", size);
            continue;
        }
        if(choice == 8){
            Print();
            continue;
        }
        int value;
        scanf("%d", &value);
        if(choice == 1){}
            FrontInsert(value);
        if(choice == 2)
            RearInsert(value);
        if(choice == 5)
            DeleteNode(value);
        if(choice == 6)
            FindNode(value);
    }
}
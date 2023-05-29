#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

void createList(struct node *head, int n){
    struct node *temp = head;
    for (int i = 0; i<n; i++){
        int num;
        scanf("%d", &num);
        temp->data = num;
        if (i != n-1){
            struct node *new = (struct node *)malloc(sizeof(struct node));
            temp->next = new;
            temp = new;
        }
        else{
            temp->next = NULL;
        }
    }
}

void printList(struct node *head){
    struct node *p = head;
    while(p!=NULL){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}

void insert(struct node *head, int pos, int num){
    struct node *prev = head;
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->data = num;
    if (pos == 0){
        new->next = head;
        head = new;
    }
    else{
        for (int i =0; i<pos-1; i++){
            prev = prev->next;
        }
        new->next = prev->next;
        prev->next = new;
    }
    printList(head);
}



int main(){
    int n;
    scanf("%d", &n);
    struct node *head = (struct node *)malloc(sizeof(struct node));
    createList(head,n);
    printf("Original list: ");
    printList(head);
    printf("\n");
    printf("Enter element to insert: ");
    int num; scanf("%d", &num);
    printf("At which position to insert (0 based indexing nodes): ");
    int pos; scanf("%d", &pos);
    printf("\n");
    insert(head,pos,num);
}
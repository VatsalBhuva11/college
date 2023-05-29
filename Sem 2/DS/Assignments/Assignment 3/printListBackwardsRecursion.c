#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct node * createList(struct node *head, int n){
    struct node *temp = head;
    for (int i = 0; i<n; i++){
        int num;
        scanf("%d", &num);
        temp->data = num;
        if (i==n-1){
            temp->next = NULL;
            return temp;
        }
        else{
            struct node *new = (struct node *)malloc(sizeof(struct node));
            temp->next = new;
            temp = new;
        }
    }
}

void printList(struct node *head){
    while (head != NULL){
        printf("%d ",head->data);
        head = head->next;
    }
    printf("\n");
}

void revPrint(struct node *head){
    if (head->next==NULL){
        printf("%d\n",head->data);
        return;
    }
    else{
        revPrint(head->next);
        printf("%d ", head->data);
    }
}

int main(){
    int n;
    scanf("%d", &n);
    struct node *head = (struct node *)malloc(sizeof(struct node));
    struct node *end = createList(head,n);
    printf("Original List: ");
    printList(head);
    printf("List in reverse: ");
    revPrint(head);
}
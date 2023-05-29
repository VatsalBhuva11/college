#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

void insert_q (struct node **head, struct node **element){ //insert before head
    printf("Enter element to insert in queue: ");
    int num;
    scanf("%d", &num);
    (*element)->data=num;
    (*element)->next = *head;
    *head = *element;
}

struct node *delete_q(struct node **head){
    struct node *temp = *head;
    while (temp->next->next != NULL){
        temp = temp->next;
    }
    struct node *last = temp->next;
    temp->next = NULL;
    return last;
}

void printList(struct node *p){
    while (p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main(){
    int n;
    scanf("%d", &n);
    struct node *head = (struct node *)malloc(sizeof(struct node));
    struct node *temp = head;
    for (int i = 0;i<n; i++){
        int num;
        scanf("%d", &num);
        temp->data = num;
        if (i == n-1){
            temp->next = NULL;
        }
        else{
            struct node *new = (struct node *)malloc(sizeof(struct node));
            temp->next = new;
            temp = new;
        }
    }   
    printf("Queue originally: ");
    printList(head);
    struct node *element = (struct node *)malloc(sizeof(struct node));
    insert_q(&head, &element);
    printf("Queue after inserting element: ");
    printList(head);
    struct node *last = delete_q(&head);
    printf("Element deleted: %d\n", last->data);
    printf("Queue after deletion: ");
    printList(head);
}
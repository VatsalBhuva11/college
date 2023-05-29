#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

void concatenate (struct node *head1, struct node *head2){
    struct node *temp = head1;
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = head2;
}

void printList(struct node *head){
    struct node *p = head;
    while(p!=NULL){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}

void createList(struct node *head, int n){
    struct node *vary = head;
    for (int i = 0; i<n; i++){
        int num;
        scanf("%d", &num);
        vary->data = num;
        if (i!=n-1){
            struct node *temp = (struct node *)malloc(sizeof(struct node));
            vary->next = temp;
            vary = temp;
        }
        else{
            vary->next = NULL;
        }
    }
}

int main(){
    int n1, n2;
    scanf("%d %d", &n1, &n2);
    struct node *head1 = (struct node *)malloc(sizeof(struct node));
    struct node *head2 = (struct node *)malloc(sizeof(struct node));
    createList(head1,n1);
    createList(head2,n2);
    printf("Original Lists:\n");
    printf("List 1: ");
    printList(head1);
    printf("List 2: ");
    printList(head2);
    concatenate(head1, head2);
    printf("Concatenated Lists: ");
    printList(head1);
}
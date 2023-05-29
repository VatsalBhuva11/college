#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

void createPoly(struct node *head, int n){
    struct node *temp = head;
    for (int i = 0; i<n; i++){
        int num;
        scanf("%d", &num);
        temp->data = num;
        if (i==n-1){
            temp->next = NULL;
        }
        else{
            struct node *new = (struct node *)malloc(sizeof(struct node));
            temp->next = new;
            temp = new;
        }
    }
}

struct node * change(struct node *head){
    struct node *add;
    add->data = 100;
    add->next=head;
    head = add;
    return head;
}

void printList(struct node * head){
    struct node *p = head;
    while (p!=NULL){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}

int main(){
    int n;
    scanf("%d", &n);
    struct node *head;
    createPoly(head,n);
    printList(head);
    head = change(head);
    printList(head);

}
#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

void createList(struct node *head, int n){
    struct node *temp = head;
    for (int i = 0; i<n; i++){
        scanf("%d", &(temp->data));
        if (i==n-1) temp->next = NULL;
        else{
            struct node *new = (struct node *)malloc(sizeof(struct node));
            temp->next = new;
            temp = new;
        }
    }
}

void printList(struct node *head){
    while (head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int flag = 1; //check if last node made null or not
void revLL(struct node **head, struct node *prev, struct node *temp){
    if (temp->next != NULL) revLL(head, prev->next, temp->next);
    if (flag) {
        *head = temp;
        flag = 0;
    }
    temp->next = prev;
    prev->next = NULL;
    
    //og thought:
    /*
    if (temp->next == NULL){
        prev->next = NULL;
        temp->next = prev;
        *head = temp;
        return;
    }
    else{
        revLL(head, prev->next, temp->next, headCopy);
        if (temp == headCopy->next){
            temp->next = prev;
            prev->next = NULL;
        }
        else{
            temp->next = prev;
        }
        return;
    }
    */
}

int main(){
    int n;
    scanf("%d", &n);
    struct node *head = (struct node *)malloc(sizeof(struct node));
    createList(head,n);
    printf("Original List: ");
    printList(head);
    revLL(&head, head, head->next);
    printf("Reversed List: ");
    printList(head);

}
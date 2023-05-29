#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

void createList(struct node *head, int n){
    struct node *temp = head;
    struct node *last;
    for (int i = 0; i<n; i++){
        int num;
        scanf("%d", &num);
        temp->data = num;
        if (i==n-1){
            temp->next = NULL;
            last = temp;
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

struct node * reverse(struct node *head){
    struct node *prev = head, *temp = head->next; 
    if (temp == NULL) return prev; //if length of linked list is 1
    struct node *fwd = head->next->next;
    while (fwd != NULL){
        temp->next = prev;
        if (prev == head){
            prev->next = NULL;
        }
        if (fwd->next == NULL){
            head = fwd;
            fwd->next = temp;
            return fwd;
        }
            prev = temp;
            temp = fwd;
            fwd = fwd->next;
        }
    if (fwd == NULL){ //if length of linked list is 2
        prev->next = NULL;
        temp->next = prev;
        return temp;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    struct node *head = (struct node *)malloc(sizeof(struct node));
    createList(head, n);
    printf("Original List: ");
    printList(head);
    head = reverse(head);
    printf("Reversed List: ");
    printList(head);


}


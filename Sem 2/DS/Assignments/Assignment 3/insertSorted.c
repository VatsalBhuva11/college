#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printList(struct node * head){
    struct node *p = head;
    while (p!=NULL){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}

struct node * insert(struct node *head, int num){
    struct node *temp = head;
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->data = num;
    if (temp->data > num){
        new->next = head;
        head = new;
    }
    else{
        int flag = 0;
        while (temp->next != NULL){
            if (temp->next->data > num){
                new->next = temp->next;
                temp->next = new;
                flag = 1;
                break;
            }
            temp = temp->next;
        }
        if (flag == 0){
            new->next = NULL;
            temp->next = new;
        }
    }
    return head;
}

int main(){
    
    int n;
    scanf("%d", &n);
    struct node *head = (struct node *)malloc(sizeof(struct node));
    struct node *copy = head;
    struct node *end;

    for (int i =0; i<n; i++){
        int num;
        scanf("%d", &num);
        copy->data = num;
        if (i != n-1){
            struct node *temp = (struct node *)malloc(sizeof(struct node));
            copy->next = temp;
            copy = temp;
        }
        else{
            copy-> next = NULL;
            end = copy;
        }
    }
    copy = head;
    printf("Original List: ");
    printList(head);
    for (int i = 0; i<n-1; i++){
        while(copy != end){
            if ((copy->data) > (copy->next->data)){
                swap(&(copy->data), &(copy->next->data));
            }
            copy = copy->next;
        }
        end = copy;
        copy = head;
    }
    printf("Sorted List: ");
    printList(head);
    printf("Enter number to insert: ");
    int num;
    scanf("%d", &num);
    head = insert(head, num);
    printf("List after inserting num in sorted list: ");
    printList(head);
return 0;
}
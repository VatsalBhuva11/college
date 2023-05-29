#include <stdio.h>
#include <stdlib.h>

int n; //so we can directly update n after insertion or deletion

struct node{
    int data;
    struct node *next;
};

struct node * createList(struct node *head){
    struct node *temp = head;
    struct node *last;
    for (int i = 0; i<n; i++){
        int num;
        scanf("%d", &num);
        temp->data=num;
        if (i != n-1){
            struct node *new = (struct node *)malloc(sizeof(struct node));
            temp->next = new;
            temp = new;
        }
        else{
            last = temp;
            last->next = head;
        }
    }
    return last;
}

void printList(struct node *head, struct node *last){
    struct node *temp = head;
    while (temp != last){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d\n", temp->data); //since last node data not printed in loop
    
    /* use below to verify insertion in circular list */
    // temp = temp->next;
    // printf("%d ", temp->data); //since last node data not printed in loop
    // temp = temp->next;
    // printf("%d\n", temp->data); //since last node data not printed in loop
}

struct node * insert(struct node *head, struct node *last, int num, int pos){
    struct node *new = (struct node *)malloc(sizeof(struct node));
    struct node *temp = head;
    new->data = num;
    if (pos == 0){ //inserting at head
        new->next = head;
        head = new;
        last->next = head;
        n = n+1;
        return head;
    }
    else if(pos == n){ //inserting after last
        new->next = head;
        last->next = new;
        last = new;
        n = n+1;
        return last;
    }
    else{
        for (int i = 0; i<pos-1; i++){ //take temp pointer to the pointer where we want to insert
            temp = temp->next;
        }
        new->next = temp->next;
        temp->next = new;
        n = n+1;
        return head;
    }
    
}

void delete(struct node **head, struct node **last, int num){
    struct node *temp = *head;
    struct node *prev = *head;
    while (temp != *last){
        if (temp->data == num){ //check if element exists in the linked list or not.
            if (temp == *head){ //if yes and if element is at head, accordingly update head and last.
                (*last)->next = (*head)->next;
                // free(head);
                *head = (*last)->next;
                n = n-1;
                return;
            }
            else{ //in case element present but not at head or last
                prev->next = temp->next;
                free(temp);
                n = n-1;
                return;
            }
        }
        if (temp != *head) prev = prev->next; //keep track of previous node to make necessary adjustments post-deletion.
        temp = temp->next;
    }
    if (temp->data == num){ //checking separately for last node
        prev->next = *head;
        free(*last);
        *last = prev;
        n = n-1;
        return;
    }
    else{
        printf("No such element exists.\n");
        return;
    }
}

int main(){
    scanf("%d", &n);
    struct node *head = (struct node *)malloc(sizeof(struct node));
    struct node *last;
    last = createList(head);
    printf("Original Circular list: ");
    printList(head, last);
    int num;
    printf("Enter number to insert: ");
    scanf("%d", &num);
    int pos;
    printf("At which position to insert(0 based nodes (0 to n)): ");
    scanf("%d", &pos);
    if (pos == 0) head = insert(head,last,num,pos); //update head if inserted at 0th pos
    else if(pos == n) last = insert(head,last,num,pos); //update last if inserted at last;
    else head = insert(head,last,num,pos); //no need to update either but need to assign the return pointer.

    printf("List after inserting element: ");
    printList(head,last);
    printf("Enter number to delete: ");
    scanf("%d", &num);
    delete(&head, &last, num);
    
    printf("List after deleting element:");
    printList(head, last);
}
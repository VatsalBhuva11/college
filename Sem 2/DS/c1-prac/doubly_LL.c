#include <stdio.h>
#include <stdlib.h>

struct node{
    struct node *prev;
    int data;
    struct node *next;
};
int n;

void create(struct node **head, int n){
    struct node *temp = *head;
    for (int i = 0; i<n; i++){
        struct node *new = (struct node *)malloc(sizeof(struct node));
        scanf("%d", &new->data);
        new->next = NULL; //setting default value as NULL
        if (temp == NULL){
            temp = new;
            *head = new;
            new->prev = NULL;
        }
        else{
            temp->next = new; //temp acts as prev for new, when temp is not NULL
            new->prev = temp;
            temp = temp->next; //update temp for next new in next iteration
        }
    }
}

void insert(struct node **head, int element, int pos){
    struct node *temp = *head; struct node *last;
    for (int i = 0; i<pos; i++){
        if (pos == n){
            if (i == n-1) last = temp; //since temp becomes NULL, so temp->prev not defined
        }
        temp = temp->next;
    }
    struct node *new = (struct node *)malloc(sizeof(struct node));
    
    new->data = element;
    new->next = temp;
    if (pos == n){ //inserting at end
        new->prev = last;
        last->next = new;
        n++;
        return;
    }
    n++; //update n after insertion
    new->prev = temp->prev;
    if (pos == 0) *head = new; //inserting at beginning
    else temp->prev->next = new; //inserting at middle
    temp->prev = new;
}

void delete(struct node **head, int pos){
    struct node *temp = *head;
    if (pos == 0){
        temp->next->prev = NULL;
        *head = (*head)->next;
        free(temp);
    }
    else{
        for (int i = 0; i<pos; i++){
            temp = temp->next;
        }
        if (pos == n-1){ //deleting end
            temp->prev->next = NULL;
            free(temp);
        }
        else{
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp);
        }
    }
    n--;
}

void printListFwd(struct node *head){
    while (head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void printListBwd(struct node *head){
    while (head->next != NULL){
        head = head->next;
    }
    while (head != NULL){ //coming through previous connections
        printf("%d ", head->data);
        head = head->prev;
    }
    printf("\n");
}



int main(){
    struct node *head = (struct node *)malloc(sizeof(struct node));
    head = NULL;
    scanf("%d", &n);
    create(&head, n);
    printf("List printed through fwd links: ");
    printListFwd(head);
    printf("List printed through bwd links: ");
    printListBwd(head);

    printf("List after 3 insertions:\n");
    insert(&head, 50, 1);
    insert(&head, 10, 0);
    insert(&head, 100, n);
    printListFwd(head);
    printListBwd(head);
    printf("\n");

    printf("List after 3 deletions:\n");
    delete(&head, 0);
    printListFwd(head);
    printListBwd(head);
    printf("\n");
    delete(&head, 1);
    printListFwd(head);
    printListBwd(head);
    printf("\n");
    delete(&head, n-1);
    printListFwd(head);
    printListBwd(head);
    
}
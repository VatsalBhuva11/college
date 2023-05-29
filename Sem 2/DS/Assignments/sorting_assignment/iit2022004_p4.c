#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};
typedef struct node link;

void create(link **head, int n){
    link *temp = *head;
    for (int i = 0; i<n; i++){
        link *new = (link *)malloc(sizeof(link));
        scanf("%d", &(new->data));
        new->next = NULL;
        if (*head == NULL){
            *head = new;
            temp = new;
        }
        else{
            temp->next = new;
            temp = new;
        }
    }

}

void delete(link **head, int element){
    link *temp = *head;
    if (temp->data == element){
        *head = (*head)->next;
        free(temp);
    }
    else{
        while (temp->next->data != element){
            temp = temp->next;
        }
        link *del = temp->next;
        temp->next = del->next;
        free(del);
    }
}

void insertAtBeginning(link **head, int element){
    link *new = (link *)malloc(sizeof(link));
    new->data = element;
    new->next = *head;
    *head = new;
}

void printList(link *head){
    while (head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n\n");
}

int main(){
    int n;
    printf("Enter size of linked list: ");
    scanf("%d", &n);
    link *head = (link *)malloc(sizeof(link));
    head = NULL;
    create(&head, n);
    printf("Original List: ");
    printList(head);
    int amount;
    printf("Self-organizing list using Move-To-Front method:\n");
    printf("Enter number of elements to search for: ");
    scanf("%d", &amount); printf("\n");
    int num;
    for (int i = 0; i<amount; i++){
        printf("Enter element to search for: ");
        scanf("%d", &num);
        printf("Self-organized list after %d iterations: ",i+1);
        delete(&head, num);
        insertAtBeginning(&head, num);
        printList(head);
    }
}
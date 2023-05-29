/*
VATSAL BHUVA
IIT2022004
Assignment 11 - Problem 4
*/
#include <stdio.h>
#include <stdlib.h>

struct linked{
    int d;
    struct linked *next;
};
typedef struct linked ELEMENT;
typedef ELEMENT *LINK;

void display(LINK head);
void insertEnd(LINK head);
void deleteFirst(LINK head);


int main(){
    
    LINK head;
    head = (LINK)malloc(sizeof(ELEMENT));
    head->next = NULL;
    
    int i = 1;
    LINK ptr = head, ptr2;
    while(i<=10){
        ptr2 = (LINK)malloc(sizeof(ELEMENT));
        ptr->d = i;
        ptr->next = ptr2; //assign next of current node to address of next node
        if (i==10) ptr->next = NULL;
        ptr=ptr->next; //move ptr front
        i++;
    }
    display(head);
    printf("Linked list after inserting a node at the end:\n");
    insertEnd(head);
    printf("Linked List after deleting first node: \n");
    deleteFirst(head);
    
return 0;
}


void display(LINK head){
    LINK ptr;
    for(ptr = head; ptr!= NULL; ptr = ptr->next){
        printf("%d\n", ptr->d);
    }
    printf("\n");
}

void insertEnd(LINK head){
    LINK ptr = head;
    while (ptr->next != NULL)
        ptr = ptr->next;
    LINK new;
    new = (LINK)malloc(sizeof(ELEMENT));
    new->next = NULL;
    new->d = 11;
    ptr->next = new;
    display(head);
}

void deleteFirst(LINK head){
    LINK ptr = head;
    head = head->next;
    free(ptr);
    display(head);
}
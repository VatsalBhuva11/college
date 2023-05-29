/*
VATSAL BHUVA
IIT2022004
Assignment 11 - Problem 4
*/
#include <stdio.h>
#include <stdlib.h>

int main(){
    
    struct linked{
        int d;
        struct linked *next;
    };
    typedef struct linked ELEMENT;
    typedef ELEMENT *LINK;

    LINK head;
    head = (LINK)malloc(sizeof(ELEMENT));
    
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
    
    for(ptr = head; ptr != NULL; ptr = ptr->next){
        printf("%d\n", ptr->d);
    }

return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};
typedef struct node stack;

void push(stack **top, int element){
    stack *new = (stack *)malloc(sizeof(stack));
    new->data = element;
    if (new == NULL){
        printf("Stack is full\n");
        exit(-1);
    }
    if (*top == NULL){ //pushing first element inside stack;
        new->next = NULL;
        *top = new;
    }
    else{
        new->next = *top;
        *top = new;
    }
}

void pop(stack **top){
    if (*top == NULL){
        printf("Stack is empty\n");
        exit(-1);
    }
    else{
        stack *temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

void printStack(stack *top){
    while (top != NULL){
        printf("%d ", top->data);
        top = top->next;
    }
    printf("\n");
}

int main(){
    stack *top = NULL;
    push(&top, 1);
    printStack(top);
    push(&top, 2);
    printStack(top);
    push(&top, 3);
    printStack(top);
    push(&top, 4);
    printStack(top);
    push(&top, 5);
    printStack(top);
    pop(&top);
    printStack(top);
    pop(&top);
    printStack(top);
    pop(&top);
    printStack(top);
    pop(&top);
    printStack(top);
    pop(&top);
    printStack(top);
    pop(&top);
    printStack(top);

}
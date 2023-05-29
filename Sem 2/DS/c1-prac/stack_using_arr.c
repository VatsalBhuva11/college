#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

struct lifo{
    int arr[MAXSIZE];
    int top;
};
typedef struct lifo stack;

void push(stack *s, int element){
    if ((s->top) == MAXSIZE-1){
        printf("Stack is full\n");
        exit(-1);
    }
    (s->top)++;
    (s->arr)[s->top] = element;
}

void pop(stack *s){
    if (s->top == -1){
        printf("Stack is empty\n");
        exit(-1);
    }
    (s->top)--;
}

void printStack(stack *s){
    for (int i = 0; i<=(s->top); i++){
        printf("%d ", (s->arr)[i]);
    }
    printf("\n");
}

int main(){
    stack *s = (stack *)malloc(sizeof(stack));
    s->top = -1;
    push(s, 1);
    printStack(s);
    push(s, 2);
    printStack(s);
    push(s, 3);
    printStack(s);
    push(s, 4);
    printStack(s);
    push(s, 5);
    printStack(s);
    pop(s);
    printStack(s);
    pop(s);
    printStack(s);
    pop(s);
    printStack(s);
    pop(s);
    printStack(s);
    pop(s);
    printStack(s);

}
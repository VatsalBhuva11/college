#include <stdio.h>
#include <malloc.h>

// 5 <-- 6 <-- 7 (top)
// printed as 7 6 5

struct node{
    int data;
    struct node *next;
};

typedef struct node stack;

void push(stack **top, int element){
    stack *new;
    new = (stack *)malloc(sizeof(stack));
    if (new == NULL){
        printf("Stack Overflow\n");
        exit(-1);
    }
    new->data = element;
    if (*top == NULL){
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
        printf("Stack Underflow\n");
        exit(-1);
    }
    else{
        stack *p = *top; int deleted = p->data;
        *top = (*top)->next;
        free(p);
    }
}

void traverse(stack *top){
    while (top != NULL){
        printf("%d ", top->data);
        top = top->next;
    }
    printf("\n");
}

int main(){
    stack *top = NULL;
    push(&top, 5);
    traverse(top);
    push(&top, 6);
    traverse(top);
    push(&top, 7);
    traverse(top);
    pop(&top);
    traverse(top);
    pop(&top);
    traverse(top);

}


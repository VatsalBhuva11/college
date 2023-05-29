/*
Vatsal Bhuva
IIT2022004
Queue Assignment - Question 1 (c)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100

struct fifo{
    char letter;
    struct fifo *next;
};
typedef struct fifo queue;

struct lifo{
    char st[MAXSIZE];
    int top;
};
typedef struct lifo stack;

void enqueue(queue **front, queue **rear, char letter){
    queue *new = (queue *)malloc(sizeof(queue));
    new->letter = letter;
    new->next = NULL;
    if (*front == NULL && *rear == NULL){ //if first char
        *front = new;
        *rear = new;
    }
    else{
        (*rear)->next = new;
        *rear = new;
    }
}

char dequeue(queue **front){
    if (*front == NULL){
        printf("Queue is empty\n");
        exit(-1);
    }
    else{
        queue *temp = *front;
        char c = temp->letter;
        *front = (*front)->next;
        free(temp);
        return c;
    }
}

void push(stack *s, char element){
    if (s->top == MAXSIZE){
        printf("Stack Overflow\n");
        exit(-1);
    }
    else{
        (s->top)++;
        (s->st)[s->top] = element;
    }
}

char pop(stack *s){
    if (s->top == -1){
        printf("Stack Underflow\n");
        exit(-1);
    }
    else{
        char temp = (s->st)[s->top];
        (s->top)--;
        return temp;
    }
}

void printStack(stack *s){
    for (int i = 0; i<=(s->top); i++){
        printf("%c ", (s->st)[i]);
    }
    printf("\n");
}

int main(){
    queue *front = (queue *)malloc(sizeof(queue));
    queue *rear = (queue *)malloc(sizeof(queue));
    front = NULL; rear = NULL;
    stack *s = (stack *)malloc(sizeof(stack));
    s->top = -1;
    printf("Enter string to check 'w#w^r' format: ");
    char input[MAXSIZE];
    scanf("%s", input);
    for (int i = 0; i<strlen(input); i++){
        enqueue(&front, &rear, input[i]); //push all alphabets to queue;
    }
    char removed;
    int countBefore = 0, countAfter = 0;
    while ((removed = dequeue(&front)) != '#'){
        if (front == NULL){
            printf("%s is not of format w#w^r\n", input);
            exit(-1);
        }
        // printf("%c ", removed);
        push(s, removed); //pushing the dequeued element inside stack for comparison with other half later
        countBefore++; //count of letters before #
    }
    while (front != NULL){
        if (countAfter >= countBefore){
            printf("%s is not of the format 'w#w^r'\n", input);
            exit(-1);
        }
        char curr = dequeue(&front); //dequeueing from second half of queue
        char topOfStack = pop(s); //comparing the dequeued element with stack created from first half
        // printf ("%c %c\n", curr, topOfStack);
        if (curr != topOfStack){
            printf("%s is not of format w#w^r\n", input);
            exit(-1);
        }
        countAfter++;
    }
    //if more letters before # than after #
    if (countAfter == countBefore) printf("%s is of the format 'w#w^r'\n", input);
    else printf("%s is not of the format 'w#w^r'\n", input);
    
}
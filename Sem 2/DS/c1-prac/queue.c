#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}queue;

void enqueue(queue **front, queue **rear, int element){
    queue *new = (queue *)malloc(sizeof(queue));
    new->data = element;
    new->next = NULL;
    if (*front == NULL && *rear == NULL){ //enqueueing first element
        *front = new;
        *rear = new;
    }
    else{
        (*rear)->next = new;
        *rear = new;
    }
}

void dequeue(queue **front){
    if (*front == NULL){
        printf("Queue is empty\n");
        exit(-1);
    }
    queue *temp = *front;
    *front = (*front)->next;
    free(temp);
}

void printQueue(queue *front){
    while(front != NULL){
        printf("%d ", front->data);
        front = front->next;
    }
    printf("\n");
}

int main(){
    queue *front = (queue *) malloc (sizeof(queue));
    queue *rear = (queue *) malloc (sizeof(queue));
    front = NULL; rear = NULL;
    enqueue(&front, &rear, 1);
    printQueue(front);
    enqueue(&front, &rear, 2);
    printQueue(front);
    enqueue(&front, &rear, 3);
    printQueue(front);
    enqueue(&front, &rear, 4);
    printQueue(front);
    enqueue(&front, &rear, 5);
    printQueue(front);
    dequeue(&front);
    printQueue(front);
    dequeue(&front);
    printQueue(front);
    dequeue(&front);
    printQueue(front);
    dequeue(&front);
    printQueue(front);
    dequeue(&front);
    printQueue(front);
    dequeue(&front);
    printQueue(front);
    dequeue(&front);
    printQueue(front);
}
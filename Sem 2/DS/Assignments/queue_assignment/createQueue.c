#include <stdio.h>
#include <stdlib.h>

struct fifo{
    int data;
    struct fifo *next;
};

typedef struct fifo queue;

void enqueue(queue **front, queue **rear, int data){
    queue *new = (queue *)malloc(sizeof(queue));
    new->data = data;
    new->next = NULL;
    if (*front == NULL && *rear == NULL){ //inserting first element
        *front = new;
        *rear = new;
    }
    else{
        (*rear)->next = new;
        *rear = (*rear)->next;
    }
}

void dequeue(queue **front){
    if (*front == NULL){
        printf("Empty Queue\n");
        exit(-1);
    }
    else{
        queue *temp = *front;
        *front = (*front)->next;
        free(temp);
    }
}

void printQueue(queue *front){
    while(front != NULL){
        printf("%d ",front->data);
        front = front->next;
    }
    printf("\n");
}

int main(){
    queue *front = (queue *)malloc(sizeof(queue)); //for dequeue
    queue *rear= (queue *)malloc(sizeof(queue)); //for enqueue
    front = NULL;
    rear = NULL;
    enqueue(&front, &rear, 1);
    printQueue(front);
    enqueue(&front, &rear, 2);
    printQueue(front);
    enqueue(&front, &rear, 3);
    printQueue(front);
    dequeue(&front);
    printQueue(front);
    dequeue(&front);
    printQueue(front);
    dequeue(&front);
    printQueue(front);
}
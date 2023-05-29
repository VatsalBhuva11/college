/*
Vatsal Bhuva
IIT2022004
Queue Assignment - Question 1 (b)
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

int main(){
    queue *front = (queue *)malloc(sizeof(queue));
    queue *rear = (queue *)malloc(sizeof(queue));
    front = NULL; rear = NULL;
    char input[MAXSIZE];
    printf("Enter string to check 'ww' format: ");
    scanf("%s", input);
    int n = strlen(input);
    for (int i = 0; i<n/2; i++){
        enqueue(&front, &rear, input[i]);
    }
    for (int i = n/2; i<n; i++){
        char removed = dequeue(&front);
        if (removed != input[i]){
            printf("%s is not of the format 'ww'\n", input);
            exit(-1);
        }
    }
    printf("%s is of the format 'ww'\n", input);
}
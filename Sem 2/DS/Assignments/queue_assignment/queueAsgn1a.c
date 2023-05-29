/*
Vatsal Bhuva
IIT2022004
Queue Assignment - Question 1 (a)
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
    printf("Enter string to check 'w#w' format: ");
    scanf("%s", input);
    int flag = 0;
    int countBefore = 0, countAfter = 0;
    for (int i = 0; i<strlen(input); i++){
        if (input[i] == '#'){
            flag = 1;
            continue;
        }
        else if(flag == 1){ //flag = 1 to check letters after #
            if (countAfter >= countBefore){ //more alphabets after # than before #
                printf("%s is not of the format 'w#w'\n", input);
                exit(-1);
            }
            char removed = dequeue(&front);
            countAfter++;
            if (removed != input[i]){
                printf("%s is not of the format 'w#w'\n", input);
                exit(-1);
            }
        }
        else{
            enqueue(&front, &rear, input[i]); //flag = 0 to enqueue elements before #
            countBefore++;
        }
    }
    //if no # at all in the string
    if (countAfter == countBefore) printf("%s is of the format 'w#w'\n", input);
    else printf("%s is not of the format 'w#w'\n",input);
    
}
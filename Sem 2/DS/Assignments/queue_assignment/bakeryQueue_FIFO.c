#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

struct fifo{
    int customerID;
    int token;
    struct fifo *next;
};
typedef struct fifo bakeryQueue;

//normal enqueue function for round robin
void enqueue(bakeryQueue **front, bakeryQueue **rear, bakeryQueue **new){
    if (*front == NULL && *rear == NULL){
        *front = (*new);
        *rear = (*new);
    }
    else{
        (*rear)->next = *new;
        *rear = *new;
    }
}

void enqueueSorted(bakeryQueue **front, bakeryQueue **rear, bakeryQueue **new){
    if (*front == NULL && *rear == NULL){
        *front = (*new);
        *rear = (*new);
    }
    else{
        bakeryQueue *temp = *front;
        if ((*new)->token < temp->token){ //required to insert before
            (*new)->next = temp;
            *front = (*new);
            return;
        }
        while (temp->next != NULL){
            //get temp before position to insert
            if ((*new)->token < temp->next->token) break; 
            temp = temp->next;
        }
        (*new)->next = temp->next;
        temp->next = (*new);
        if ((*new)->next == NULL){ //element inserted at last;
            *rear = *new;
        } 
    }
}

bakeryQueue *dequeue(bakeryQueue **front){
    bakeryQueue *served;
    if (*front == NULL){
        printf("No customer currently\n");
        exit(-1);
    }
    else{
        bakeryQueue *temp = *front;
        served = temp;
        *front = (*front)->next;
        return temp;
        free(temp);
        return served;
    }
}

void printQueue(bakeryQueue *front){
    while (front != NULL){
        printf("Token: %d, CustomerID: %d\n", front->token, front->customerID);
        front = front->next;
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    bakeryQueue *front = (bakeryQueue *)sizeof(bakeryQueue);
    bakeryQueue *rear = (bakeryQueue *)sizeof(bakeryQueue);
    front = NULL; rear = NULL;
    FILE *f = fopen(argv[1], "r");
    if (f == NULL){
        printf("Unable to open file\n");
        exit(-1);
    }
    int customerID, token;
    while (fscanf(f, "%d %d", &customerID, &token) != EOF){
        // printf("%d %d\n", customerID, token);
        bakeryQueue *new = (bakeryQueue *)malloc(sizeof(bakeryQueue));
        new->customerID = customerID;
        new->token = token;
        new->next = NULL;
        enqueueSorted(&front, &rear, &new);
    }
    printf("Initial Queue:\n");
    printQueue(front);
    printf("How many more customers to serve? : ");
    int n;
    scanf("%d", &n);
    for (int i = 0; i<n; i++){
        bakeryQueue *new = (bakeryQueue *)malloc(sizeof(bakeryQueue));
        printf("Enter customer ID of customer %d: ",i+1);
        scanf("%d", &(new->customerID));
        printf("Enter token of customer %d: ", i+1);
        scanf("%d", &(new->token));
        new->next = NULL;
        enqueueSorted(&front, &rear, &new);
        printf("\n");
    }
    printf("Final serving queue:\n");
    printQueue(front);

    /******************* ROUND ROBIN *********************/
    printf("Enter number of items to buy for each customer: ");
    scanf("%d", &n);
    bakeryQueue *temp;
    int count = 1;
    bakeryQueue *rearCopy;
    for (int i = 0; i<n; i++){
        rearCopy = rear;
        do{
            temp = dequeue(&front);
            printf("Customer with token %d bought item %d\n", temp->token, count);
            enqueue(&front, &rear, &temp);
            // printQueue(front);
        } while(temp != rearCopy);
        count++;
    }
}
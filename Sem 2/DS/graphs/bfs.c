#include <stdio.h>
#include <stdlib.h>
#define N 1000

struct node{
    int data;
    struct node *next;
};
struct node *adjList[N];

struct queueNode{
    int data;
    struct queueNode *next;
};
typedef struct queueNode *queue;
queue front = NULL, rear = NULL;
int visited[N];

struct node *create(int data){
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->data = data;
    new->next = NULL;
    return new;
}

int stack[N]; int top = -1;

void insert(int v1, int v2, struct node *arr[]){
    struct node *new = create(v2);
    if (arr[v1] == NULL){
        arr[v1] = new;
    }
    else{
        struct node *temp = arr[v1];
        while (temp->next != NULL) temp = temp->next;
        temp->next = new;
    }
}

queue createQueueNode(int data){
    queue new = (queue) malloc (sizeof(struct queueNode));
    new->data = data;
    new->next = NULL;
    return new;
}

int isQueueEmpty(queue front){
    if (front == NULL){
        return 1;
    }
    return 0;
}

void enqueue(queue *front, queue *rear, int data){
    queue new = createQueueNode(data);
    if (*front == NULL && *rear == NULL){
        *front = *rear = new;
    }
    else{
        (*rear)->next = new;
        (*rear) = new;
    }
}

int dequeue(queue *front, queue *rear){
    if (isQueueEmpty(*front)){
        printf("Empty queue.");
        exit(-1);
    }
    else{
        queue temp = *front; int data = temp->data;
        if (temp->next == NULL){ //dequeueing last node
            *rear = NULL;
        }
        (*front) = (*front)->next;
        free(temp);
        return data;
    }
}

void printQueue(queue front){
    while (front != NULL){
        printf("%d ", front->data);
        front = front->next;
    }
    printf("\n");
}



void printList(struct node *arr[], int vertices){
    for (int i = 1; i<=vertices; i++){
        struct node *temp = arr[i];
        printf("%d: ", i);
        if (temp == NULL) printf("\n");
        else{
            while (temp->next != NULL){
                printf("%d->", temp->data);
                temp = temp->next;
            }
            printf("%d\n", temp->data);
        }
    }
}

void push(int data){
    stack[++top] = data;
}

void printStack(){
    for (int i = 0; i<=top; i++){
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int pop(){
    if (top == -1){
        printf("Stack is empty.\n");
        exit(-1);
    }
    int data = stack[top];
    top--;
    return data;
}

int isStackEmpty(){
    if (top == -1) return 1;
    return 0;
}


void bfs(int startNode){
    // queue front = NULL, rear = NULL; made global queue instead, below struct definition.
    enqueue(&front, &rear, startNode);
    visited[startNode] = 1;
    while (!isQueueEmpty(front)){
        int deleted = dequeue(&front, &rear);
        printf("%d ", deleted);
        struct node *inAdjList = adjList[deleted];
        while (inAdjList != NULL && visited[inAdjList->data] != 1){
            enqueue(&front, &rear, inAdjList->data);
            visited[inAdjList->data] = 1;
            inAdjList = inAdjList->next;
        }
    }
}

void rdfs(int startNode){
    printf("%d ", startNode);
    visited[startNode] = 1;
    struct node *inAdjList = adjList[startNode];
    while (inAdjList != NULL){
        if (visited[inAdjList->data] != 1){
            rdfs(inAdjList->data);
        }
        inAdjList = inAdjList->next;
    }
}

void dfs(int startNode){
    push(startNode);
    while (!isStackEmpty()){
        int popped = pop();
        visited[popped] = 1;
        printf("%d ", popped);
        struct node * inAdjList = adjList[popped];
        while (inAdjList != NULL && visited[inAdjList->data] != 1){
            push(inAdjList->data);
            visited[inAdjList->data] = 1;
            inAdjList = inAdjList->next;
        }
    }
}

int main(){
    int vertices;
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    
    for (int i = 1; i<=vertices; i++) {
        adjList[i] = NULL;
        visited[i] = 0;
    }

    int edges;
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    printf("Enter pairs of vertices of edges:\n");
    for (int i = 0; i<edges; i++){
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        insert(v1, v2, adjList);
        insert(v2, v1, adjList);
    }
    printf("\nAdjacency List:\n");

    printList(adjList, vertices);

    printf("\nEnter node to start BFS from: ");
    int startNode;
    scanf("%d", &startNode);

    printf("BFS traversal with starting node %d:\n", startNode);
    bfs(startNode); printf("\n\n");

    for (int i = 1; i<=vertices; i++) {
        visited[i] = 0;
    }
    printf("DFS traversal using recursion:\n");
    rdfs(startNode); printf("\n\n");

    for (int i = 1; i<=vertices; i++) {
        visited[i] = 0;
    }
    printf("DFS traversal using stack:\n");
    dfs(startNode); printf("\n\n");

}
#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct node *create(int data){
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->data = data;
    new->next = NULL;
    return new;
}

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

int main(){
    int vertices;
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    struct node *adjList[vertices+1];
    for (int i = 1; i<=vertices; i++) adjList[i] = NULL;

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

    printList(adjList, vertices);
}
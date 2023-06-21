#include <stdio.h>

int adjMatrix[1000][1000];

int main(){

    printf("Enter number of vertices: ");
    int vertices; scanf("%d", &vertices);
    printf("Enter number of edges: ");
    int edges; scanf("%d", &edges);
    printf("Enter adjacent vertices pairs:\n");
    for (int i = 0; i<edges; i++){
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        adjMatrix[v1][v2] = 1;
        adjMatrix[v2][v1] = 1;
    }
    printf("Adjacent vertices are:\n");
    for (int i = 1; i<=vertices; i++){
        printf("%d: ",i);
        for (int j = 0; j<vertices; j++){
            if (adjMatrix[i][j] == 1){
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}
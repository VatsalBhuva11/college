#include <stdio.h>

int n;
int heap[10000];
int heapSize = 0;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(int data){
    heapSize++;
    heap[heapSize] = data;
    int temp = heapSize;
    while (heap[temp] > heap[temp/2]){
        swap(&heap[temp], &heap[temp/2]);
        temp = temp/2;
    }
}



void printHeap(int heap[], int n){
    for (int i = 1; i<=n; i++){
        printf("%d ", heap[i]);
    }
    printf("\n");
}


int main(){
    printf("Enter number of elements: ");
    scanf("%d", &n);
    heap[0] = __INT_MAX__;
    for (int i = 0; i<n; i++){
        int element;
        printf("Enter element: ");
        scanf("%d", &element);
        insert(element);
    }
    printf("MaxHeap: ");
    printHeap(heap, n);
    int k;
    printf("Enter value of k (to find kth largest element): ");
    scanf("%d", &k);
}
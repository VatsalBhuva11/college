#include <stdio.h>
#include <limits.h>

int n;
int heap[1000];
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//if entire array is passed as input
void maxHeap(int arr[], int n){
    for (int i = 1; i<=n; i++){
        int temp = i;
        while (heap[temp] > heap[temp/2]){
            swap(&heap[temp], &heap[temp/2]);
            temp = temp/2;
        }
    }
}

//if new element to be inserted.
void insert(int element){
    n++;
    int temp = n;
    heap[temp] = element;
    while (heap[temp] > heap[temp/2]){
        swap(&heap[temp], &heap[temp/2]);
        temp = temp/2;
    }
}

int deleteMax(){
    int temp = 1; int maxElem = heap[1];
    heap[1] = heap[n]; //removed max, replaced last element instead.
    n--;
    while (temp*2 <= n){
        if (temp*2 == n){
            if (heap[temp] < heap[2*temp]){
                swap(&heap[temp], &heap[2*temp]);
            }
            temp = temp*2;
        }
        else{
            if (heap[2*temp] > heap[2*temp+1]){
                if (heap[temp] < heap[2*temp]){
                    swap(&heap[temp], &heap[2*temp]);
                    temp = temp*2;
                }
                else break;
            }
            else{
                if (heap[temp] < heap[2*temp+1]){
                    swap(&heap[temp], &heap[2*temp+1]);
                    temp = temp*2+1;
                }
                else break;
            }
        }
    }
    return maxElem;
}

int kthLargest(int arr[], int k, int n){
    int ans;
    for (int i = 1; i<k; i++){
        ans = deleteMax();
    }
    return ans;
}



void printHeap(){
    for (int i = 1; i<=n; i++){
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int main(){
    printf("Enter number of elements in array: ");
    scanf("%d", &n);
    heap[0] = INT_MAX;
    for (int i = 1; i<=n; i++) scanf("%d", &heap[i]);
    maxHeap(heap, n);
    printf("Max heap: ");
    printHeap();
    int num;
    printf("Enter a number to insert: ");
    scanf("%d", &num);
    insert(num);
    printf("Heap after inserting %d: ", num);
    printHeap();

    int maxElem = deleteMax();
    printf("Heap after deleting max (%d): ",maxElem);
    printHeap();

    printf("Enter value of k to find kth largest: ");
    int k;
    scanf("%d", &k);
    kthLargest(heap, k, n);
    printf("%dth largest element is: %d\n", k, heap[1]);
}
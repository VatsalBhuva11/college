#include <stdio.h>

int n;
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void printList(int arr[], int n){
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertionSort(int arr[], int n){
    for (int i = 1; i<n; i++){
        int curr = arr[i], j;
        for (j = i-1; j>=0; j--){
            if (curr < arr[j]) arr[j+1] = arr[j];
        }
        arr[j+1] = curr;
        printList(arr, n);
    }
}

void bubbleSort(int arr[], int n){
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n-1; j++){
            if (arr[i] < arr[j]) swap(&arr[i], &arr[j]);
        }
        printList(arr,n);   
    }
}

void merge(int arr[], int low, int high){
    int mid = (low+high)/2;
    int i = low, j= mid+1, k=0;
    int tempArr[100];
    while (i <= mid && j <= high){
        if (arr[i] < arr[j]){
            tempArr[k++] = arr[i++];
        }
        else{
            tempArr[k++] = arr[j++];
        }
    }
    while (i<=mid || j<=high){
        if (i<=mid){
            tempArr[k++] = arr[i++];
        }
        else{
            tempArr[k++] = arr[j++];
        }
    }
    k = 0;
    for (int i = low; i<=high; i++){
        arr[i] = tempArr[k++];
    }
}

void mergesort(int arr[], int low, int high){
    int mid = (low+high)/2;
    if (low == high){
        return;
    }
    mergesort(arr, low, mid);
    mergesort(arr, mid+1, high);
    merge(arr, low, high);
    printf("Low = %d, High = %d : ",low,high);
    printList(arr,n);
}

int main(){
    printf("Enter size of array: ");
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    printf("Original List: ");
    printList(arr, n);

    // insertionSort(arr, n);
    // printf("Insertion Sorted List: ");
    // printList(arr, n);

    // bubbleSort(arr,n);
    // printf("Bubble Sorted List: ");
    // printList(arr,n);

    mergesort(arr,0,n-1);
    printf("Merge Sorted List: ");
    printList(arr,n);
    
}
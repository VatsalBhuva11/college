#include <stdio.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void printList(int arr[], int n){
    for (int i = 0; i<n; i++){
        printf("%d ", arr[i]);
    }

    printf("\n");
}

void selection_sort(int arr[], int n){
    for (int i = 0; i<n-1; i++){
        int minPos = i;
        for (int j = i+1; j<n; j++){
            if (arr[j] < arr[minPos]) minPos = j;
        }
        swap(&arr[i], &arr[minPos]);
        printList(arr, n);
    }
}

void insertion_sort(int arr[], int n){
    for (int i = 1; i<n; i++){
        int j = i;
        while (arr[j] < arr[j-1] && j>0){
            swap(&arr[j], &arr[j-1]);
            j--;
        }
        printList(arr, n);
    }
}

void bubble_sort(int arr[], int n){
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n-i-1; j++){
            if (arr[j+1] < arr[j]) swap(&arr[j], &arr[j+1]);
        }
    }
}

void merge_mergesort(int arr[], int low, int high){
    int mid = (low+high)/2;
    int i = low, j = mid+1, k = 0;
    int temp[100];
    while (i<=mid && j<=high){
        if (arr[i] < arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid){
        temp[k++] = arr[i++];
    }
    while (j <= high){
        temp[k++] = arr[j++];
    }
    k = 0;
    for (int i = low; i<=high; i++){
        arr[i] = temp[k++];
    }
}

void merge_sort(int arr[], int low, int high){
    if (low == high) return;
    else{
        int mid = low + (high - low)/2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid+1, high);
        merge_mergesort(arr, low, high);
    }
}

// int partition(int arr[], int low, int high){
//     int i = low-1, j = high+1;
//     int pivot = arr[low];
//     while (i<j){
//         do{
//             i++;
//         }while(arr[i]<=pivot && i<high);
//         do{
//             j--;
//         }while(arr[j]>pivot && j>=low);
//         if (i < j)
//             swap(&arr[i], &arr[j]);
//     }
//     swap(&pivot, &arr[j]); //since higher before lower now
//     return j;
// }

// void quick_sort(int arr[], int low, int high){
//     if (low < high){
//         int j = partition(arr, low, high);
//         quick_sort(arr, low, j-1);
//         quick_sort(arr, j+1, high);
//     }
// }

int partition(int A[], int low, int high) {
    int p = A[low], i = low , j=high;
    while(i < j){
        while(A[i] <= p) i++;
        while(A[j] > p) j--; //this do while was wrong
        if(i < j){
            swap(&A[i],&A[j]);
        }
    }
    swap(&A[low],&A[j]);
    return j;
}

void quickSort(int A[], int low, int high) {
    if(low < high) {
        int p = partition(A, low, high);
        quickSort(A, low, p); //Here you can just put p instead of p-1
        quickSort(A, p+1, high);
    }
}

int main(){
    printf("Enter n: ");
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    printf("Original array: ");
    printList(arr, n);

    // selection_sort(arr, n);
    // printf("Sorted array (selection sort) : ");

    // insertion_sort(arr, n);
    // printf("Sorted array (insertion sort) : ");

    // bubble_sort(arr, n);
    // printf("Sorted array (bubble sort) : ");

    merge_sort(arr, 0, n);
    printf("Sorted array (merge sort): ");

    // printf("Sorted array (quick sort): ");
    // quickSort(arr, 0, n);
    
    printList(arr, n);

}
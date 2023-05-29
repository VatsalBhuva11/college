/*
IIT2022004
Assignment 6 - Question 1
VATSAL BHUVA
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// void merge_mergesort(int arr[], int low, int high){
//     int mid = (low+high)/2;
//     int i = low, j = mid+1, k = 0;
//     int temp[10000];
//     while (i<=mid && j<=high){
//         if (arr[i] < arr[j]) temp[k++] = arr[i++];
//         else temp[k++] = arr[j++];
//     }
//     while (i <= mid){
//         temp[k++] = arr[i++];
//     }
//     while (j <= high){
//         temp[k++] = arr[j++];
//     }
//     k = 0;
//     for (int i = low; i<=high; i++){
//         arr[i] = temp[k++];
//     }
// }

// void merge_sort(int arr[], int low, int high){
//     if (low == high) return;
//     else{
//         int mid = low + (high - low)/2;
//         merge_sort(arr, low, mid);
//         merge_sort(arr, mid+1, high);
//         merge_mergesort(arr, low, high);
//     }
// }

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int arr[], int n){
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n-i-1; j++){
            if (arr[j+1] < arr[j]) swap(&arr[j], &arr[j+1]);
        }
    }
}

int main(){
    srand(time(0));
    FILE *f = fopen("input.txt", "w+");

    if (f == NULL){
        printf("File could not be opened.\n");
        exit(-1);
    }

    for (int i = 0; i<100000; i++){
        fprintf(f, "%d ", rand());
    }
    fseek(f, 0, SEEK_SET);
    int *arrays[100];
    for (int i = 0; i<100; i++){
        arrays[i] = (int *)malloc(1000*sizeof(int));
        for (int j = 0; j<1000; j++){
            fscanf(f, "%d ", &arrays[i][j]); 
        }
    }
    //sorting each array individually
    for (int i = 0; i<100; i++){
        bubble_sort(arrays[i],1000);
    }

    FILE *out = fopen("output.txt", "w+");
    if (out == NULL){
        printf("File could not be opened.\n");
        exit(-1);
    }
    int *indices = (int *)calloc(100, sizeof(int));
    int *pos, min = __INT_MAX__;
    
    for (int i = 0; i<100000; i++){
        min = __INT_MAX__;
        for (int j = 0; j<100; j++){
            if (indices[j] == -1) continue; //if an array is entirely traversed.
            else{
                if (arrays[j][indices[j]] < min){
                    min = arrays[j][indices[j]];
                    pos = &(indices[j]);
                }
            }
        }
        (*pos)++;
        if (*pos == 1000) (*pos) = -1;
        fprintf(out, "%d ", min);
    }
    
    fclose(f);
    fclose(out);
}
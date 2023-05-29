#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge_mergesort(int arr[], int low, int high){
    int mid = (low+high)/2;
    int i = low, j = mid+1, k = 0;
    int temp[10000];
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
    int arr[1000];

    FILE *temp = fopen("temp.txt", "w+");
    int j,k;
    //sorts every 1000 numbers and stores it into a temporary file.
    for (int i = 0; i<100; i++){
        for (j=i*1000; j<(i+1)*1000; j++){
            fscanf(f, "%d ", &arr[j%1000]);
        }
        merge_sort(arr, 0, 1000);
        for (k = 0; k<1000; k++){
            fprintf(temp, "%d ",arr[k]);
        }
    }

    FILE *out = fopen("output.txt", "w+");
    int *indices = (int *)calloc(100, sizeof(int));
    int *pos = 0, min = __INT_MAX__, num;
    for (int i = 0; i<1; i++){
        min = __INT_MAX__;
        int count = 0;
        for (int j = 0; j<100; j++){
            printf("%d ", indices[j]);
            if (indices[j] != -1){
                while (count != (j*1000 + indices[j])){
                    printf("%d ", count);
        //             //to reach to the required word
                    while (fgetc(temp) != ' ') continue;
                    count++;
                }
        //         fscanf(temp, "%d ", &num);
        //         printf("%d ", num);
        //         if (num < min){
        //             min = num;
        //             pos = &indices[j];
        //         }
        //     }
        //     else{
        //         continue;
            }
        }
        // (*pos)++;
        // if ((*pos) == 1000) *pos = -1;
        fprintf(out, "%d ", min);
        fseek(temp, 0, SEEK_SET);
    }



}
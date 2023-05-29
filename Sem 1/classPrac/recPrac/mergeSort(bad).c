#include <stdio.h>
#include <printArr.h>

void mergeSort(int arr[], int low, int high);
void merge(int arr[], int low, int m, int high);


int main(){
    int n;
    printf("Enter size of array: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter elements of array:\n");
    for (int i = 0; i < n; i++){
        scanf("%d",&arr[i]);
    }
    mergeSort(arr,0,n);
    print1DArr(arr,n);
}

void mergeSort(int arr[], int low, int high){
    int m;
    if (low < high){
        m = (low+high)/2;
        mergeSort(arr,low,m);
        mergeSort(arr,m+1,high);
        merge(arr,low,m,high);
    }
}

void merge(int arr[], int low, int m, int high){
    int i,j,k;
    int arr2[high];
    for (int i = low; i< high; i++){
        arr2[i]=arr[i];
    }
    i = low; j=m+1; k=low;
    while (i < m && j<high){
        if (arr2[i]<=arr2[j]) arr[k++]=arr2[i++];
        else arr[k++] = arr2[j++];
    }
    while (i<=m) arr[k++] = arr2[i++];
    

}
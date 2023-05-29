#include <stdio.h>
#include <printArr.h>

int main(){
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    printf("Original array: ");
    print1DArr(arr,n);
    for (int i = 0; i<n-1; i++){
        for (int j = 0; j<n-i-1;j++){
            if (arr[j]<arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    printf("Sorted array: ");
    print1DArr(arr,n);
}
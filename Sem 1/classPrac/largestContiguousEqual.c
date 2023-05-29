#include <stdio.h>
#include <printArr.h>

int main(){
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int arr[n];
    int count = 1,max=0,reqNum;
    for (int i = 0; i < n; i++){
        printf("Enter num: ");
        scanf("%d", &arr[i]);
    }
    
    for (int i = 0; i < n; i++){
        count = 1; 
        while (arr[i] == arr[i+1]){
            count++; i++;
            if (i== n-1) break;
        }
        if (count > max) {max = count; reqNum = arr[i];}
    }
    printf("Array is: "); print1DArr(arr,n);
    printf("largest contiguous sequence is of %d, with length %d\n", reqNum,max);
}
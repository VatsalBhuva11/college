#include <stdio.h>
#include <printArr.h>

int main(){
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter 0th element: ");
    scanf("%d", &arr[0]);
    for (int i = 1; i < n; i++){
        printf("Enter %dth element: ",i);
        scanf("%d", &arr[i]);
        for (int j = i; j>0; j--){
            if (arr[j] > arr[j-1]){
                int temp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("The array sorted in descending order is: "); print1DArr(arr,n);
    printf("The 6th largest number is: %d", arr[5]);

}
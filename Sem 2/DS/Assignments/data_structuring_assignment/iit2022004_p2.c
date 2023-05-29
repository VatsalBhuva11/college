#include <stdio.h>

int main(){
    int n;
    printf("Enter number of elements in array: ");
    scanf("%d", &n);
    int arr[100];
    for (int i = n; i<=2*n-1; i++){
        scanf("%d", &arr[i]);
    }
    for (int i = 2*n-2; i>1; i-=2){
        if (arr[i] >= arr[i+1]) arr[i/2] = arr[i];
        else arr[i/2] = arr[i+1];
    }
    int max = arr[1];
    printf("MAX: %d\n", max);
    arr[1] = -1;
    //downward traversal to reduce the max to calculate the next max
    for (int i = 1; i<=2*n-1;){
        if (arr[2*i] == max) {
            arr[2*i] = -1;
            i = 2*i;
        }
        else {
            arr[2*i + 1] = -1;
            i = 2*i + 1;
        }
    }
    //upward traversal
    for (int i = 2*n-2; i>1; i-=2){
        if (arr[i] >= arr[i+1]) arr[i/2] = arr[i];
        else arr[i/2] = arr[i+1];
    }
    int next_max = arr[1];
    printf("NEXT MAX: %d\n", next_max);

}
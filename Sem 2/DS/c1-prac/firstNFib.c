#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i<n; i++){
        if (i == 0 || i == 1) arr[i] = 1;
        else arr[i] = arr[i-1] + arr[i-2];
    }
    printf("First %d fib numbers are: ",n);
    for (int i = 0; i<n ; i++){
        printf("%d ", arr[i]);
    }
}
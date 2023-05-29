#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int i = 0;
    int arr[n]; int num = 3; int count = 1;
    arr[0] = 2;
    while (i<n){
        int flag = 1;
        for (int j = 0; j<count; j++){
            if (num%(arr[j]) == 0){
                flag = 0;
                break;
            }
        }
        if (flag){
            arr[count++] = num;
            i++;
        }
        num += 2;
    }
    printf("First %d prime numbers are: ", n);
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
}
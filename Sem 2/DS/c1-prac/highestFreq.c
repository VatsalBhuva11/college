#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    int max = 0; int num; int count;
    for (int i = 0; i<n; i++){
        count = 1;
        if (arr[i] != -1){
            for (int j = i+1; j<n; j++){
                if (arr[j] == arr[i]){
                    count++;
                    arr[j] = -1;
                }
            }
            if (count > max){
                max = count;
                num = arr[i];
            }
        }
    }
    printf("Highest frequency is of %d, freq is %d\n", num, max);
}
/*
Vatsal Bhuva IIT2022004 Assignment 4
*/
#include <stdio.h>

int main(){
    int N;
    int a = 0, b = 1;
    printf("Enter positive value of N: ");
    scanf("%d", &N);
    printf("%d ", b);
    for (int i = 0; i < N-1; i++){
        int temp = a;
        a = b;
        b = a + temp;
        printf("%d ", b);
    }
}
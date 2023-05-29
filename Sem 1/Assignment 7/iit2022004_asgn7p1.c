/*
VATSAL BHUVA
IIT2022004
Assignment 7 - Problem 1
*/
#include <stdio.h>

int sum(int n){
    if (n%10==n) return n;
    return ((n%10)+sum(n/10));
}

int main(){
    int n;
    printf("Enter a number: ");
    scanf("%d",&n);
    printf("Sum of digits of number using recursion: %d\n",sum(n));
}
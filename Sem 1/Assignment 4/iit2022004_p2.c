/*
Vatsal Bhuva IIT2022004 Assignment 4
*/
#include <stdio.h>

int main(){
    int a,b;
    printf("Enter two numbers (smaller, greater):\n");
    scanf("%d %d", &a, &b); //a<b
    int c = a, d = b; //to store original values of a and b
    if (a == 0){
        printf("0 cannot have a GCD.");
    }
    while (b%a != 0){
        int rem = b%a;
        b = a;
        a= rem;
    }
    
    printf("GCD of %d and %d is %d", c, d, a);
}
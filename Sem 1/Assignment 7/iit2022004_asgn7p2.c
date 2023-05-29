/*
VATSAL BHUVA
IIT2022004
Assignment 7 - Problem 2
*/
#include <stdio.h>
#include <math.h>

int g(int x){
    if (x==1) return 6;
    else if(x>1){
        return (x+4*g(x/2));
    }   
}

int f(int x){
    long int m = pow(10,9)+7;
    return (g(pow(2,x))%m);
}


int main(){
    int x;
    printf("Enter value of x: ");
    scanf("%d", &x);
    int ans = f(x);
    printf("for x = %d, f(x) = %d\n",x,f(x));
}
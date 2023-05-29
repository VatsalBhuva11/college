/*
Vatsal Bhuva
IIT2022004
Assignment 9 - Problem 1
*/
#include <stdio.h>

int main(){
    float x,y;
    float *p1 = &x;
    float *p2 = &y;
    printf("Enter two numbers: ");
    scanf("%f %f", &x, &y);
    float sum = *p1 + *p2;
    printf("Sum of two numbers is: %f", sum);
}
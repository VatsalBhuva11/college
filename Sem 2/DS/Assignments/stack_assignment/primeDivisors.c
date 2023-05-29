#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 100

int checkPrime(int n){
    for (int i = 2; i<n; i++){
        if (n%i==0){
            return 0; //not prime
        }
    }
    return 1;
}

void push(int stack[], int *top, int element){
    if (*top == MAXSIZE){
        printf("Stack Overflow\n");
        exit(-1);
    }
    else{
        *top = *top + 1;
        stack[*top] = element;
    }
}

void printStack(int stack[], int top){
    for (int i = 0; i<=top; i++){
        printf("%d ",stack[i]);
    }
    printf("\n");
}

int main(){
    int n;
    printf("Enter number: ");
    scanf("%d", &n);
    int stack[MAXSIZE]; int top = -1;
    if (checkPrime(n)){
        stack[++top] = n;
        printStack(stack, top);
        return 0;
    }
    for (int i = 2; i<=n/2; i++){
        if (n%i==0 && checkPrime(i)==1){
            push(stack, &top, i);
        }
    }
    printStack(stack, top);

}
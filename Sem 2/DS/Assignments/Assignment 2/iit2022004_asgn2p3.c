/*
Assignment 2 - Problem 3
Vatsal Bhuva
IIT2022004
*/
#include <stdio.h>
#include <stdlib.h>

struct cricketer{
    char name[20];
    int runs;
    float avg;
};

int main(){
    
    int n;
    printf("Enter number of cricketers: ");
    scanf("%d", &n);
    struct cricketer *arr;
    arr = (struct cricketer *)malloc(n * sizeof(struct cricketer));
    for (int i = 0; i<n; i++){
        printf("Enter name of cricketer %d: ",i+1);
        scanf("%s", (arr+i)->name);
        printf("Enter runs of cricketer %d: ",i+1);
        scanf("%d", &((arr+i)->runs));
        printf("Enter avg of cricketer %d: ",i+1);
        scanf("%f", &((arr+i)->avg));
        printf("\n");
    }
    printf("\n");
    for (int i =0; i<n; i++){
        printf("Details of cricketer %d:\n",i+1);
        printf("Name: %s\n", (arr+i)->name);
        printf("Runs: %d\n", (arr+i)->runs);
        printf("Average runs: %f\n", (arr+i)->avg);
        printf("\n");
    }
    
return 0;
}
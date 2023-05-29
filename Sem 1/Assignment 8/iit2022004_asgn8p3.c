/*
VATSAL BHUVA
IIT2022004
Assignment 8 - Problem 3
*/

#include <stdio.h>

struct customers{
    char name[100];
    int accNo;
    float balance;
};

void names(struct customers a[], int n){
    printf("Customers having balance less than $200:\n");
    for (int i = 0; i<n; i++){
        if (a[i].balance < 200){
            printf("%s\n", a[i].name);
        }
    }
    printf("\n");
}

void increment(struct customers a[], int n){
    printf("Increment balance of customers with balance > $1000:\n");
    for (int i = 0; i < n; i++){
        if (a[i].balance>1000){
            printf("Old balance of customer %s was: %f\n",a[i].name,a[i].balance);
            a[i].balance+=100;
            printf("New balance of customer %s is: %f\n",a[i].name,a[i].balance);
            printf("\n");
        }
    }
    
}

int main(){
    int n=0;
    do{
        printf("Enter number of customers: ");
        scanf("%d", &n);
    }while (n<5);
    
    struct customers details[n];
    for (int i = 0; i<n; i++){
        printf("Customer %d:\n",i+1);
        printf("Enter name of customer: ");
        scanf("%s",&details[i].name);
        printf("Enter account number of customer: ");
        scanf("%d",&details[i].accNo);
        printf("Enter balance of customer: ");
        scanf("%f",&details[i].balance);
    }
    printf("\n");

    names(details, n);
    increment(details,n);
}
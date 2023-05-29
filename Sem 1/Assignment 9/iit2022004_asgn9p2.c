/*
Vatsal Bhuva
IIT2022004
Assignment 9 - Problem 2
*/

void inputArray(int *arr, int size);
int search(int *arr, int size, int toSearch);

#include <stdio.h>

int main(){
    int size;
    printf("Enter size of array: ");
    scanf("%d", &size);
    int arr[size];
    inputArray(arr, size);
    int num;
    printf("Enter number to search: ");
    scanf("%d", &num);
    int ans = search(arr,size,num);
    if (ans==1) printf("%d is present in the array.\n",num);
    else printf("%d is not present in the array.\n",num);
}

void inputArray(int *arr, int size){
    for (int i = 0; i<size; i++){
        printf("Enter element of array: ");
        scanf("%d", arr+i);
    }
}

int search(int *arr, int size, int toSearch){
    for (int i = 0; i<size; i++){
        if (*(arr+i)==toSearch){
            return 1;
        }
    }
    return 0;
}
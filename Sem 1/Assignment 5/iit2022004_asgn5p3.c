/*
Vatsal Bhuva
IIT2022004
Problem 3 (Assignment 5)
*/

#include <stdio.h>

int main(){
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n], unique[n];
    for (int i = 0; i < n; i++){
        unique[i] = 0; //initialise all elements of unique as 0
    }
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
        unique[arr[i]-1] += 1;
        //above statement keeps count of each unique element of arr for diff indices of unique.
    }
    for (int i = 0; i < n; i++){
        if (unique[i] != 0){
            printf("Occurences of %d = %d",i+1, unique[i]);
        //the number is i+1 since we stored the count of a number in arr[i]-1 index of unique.
        }
        printf("\n");
    }
    return 0;

}
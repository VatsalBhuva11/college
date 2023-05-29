/*
Homework Assignment 3 - Question 4
VATSAL BHUVA
IIT2022004
*/
#include <stdio.h>

void inputArray(int *arr, int n){
    for (int i = 0; i<n; i++){
        scanf("%d", arr+i);
    }
}
void printArray(int arr[], int n){
    for (int i = 0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int compute(int arr1[], int arr2[], int s, int t){
    //if arr1[i] > x numbers in arr2, then arr1[i+1] > x as well. keeping track of x using count
    int count = 0; 
    int ans = 0;
    int i = 0, j = 0;
    while (i < s && j < t){
        if (arr1[i] > arr2[j]){
            count++;
            j++; //move j ahead to compare arr1[i] with other elements in j
        }
        else{
            ans += count; 
            i++; //move i ahead, and add count to ans (shows how many numbers in arr2 less than arr1[i])
        }
    }
    if (i<s){ //if entire arr2 traversed, some elements in arr1 remain who are greater than all elements in arr2
        ans += (s-i) * t;
    }
    return ans;
}

int main(){
    int s,t;
    printf("Enter value of s: ");
    scanf("%d", &s);
    printf("Enter value of t: ");
    scanf("%d", &t);
    int arr1[s], arr2[t];
    inputArray(arr1, s); inputArray(arr2, t);
    printf("\n");
    printf("Array 1: ");
    printArray(arr1, s);
    printf("Array 2: ");
    printArray(arr2, t);
    printf("Answer: %d",compute(arr1,arr2,s,t));
}
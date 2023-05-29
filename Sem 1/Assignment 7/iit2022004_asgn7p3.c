/*
VATSAL BHUVA
IIT2022004
Assignment 7 - Problem 3
*/

#include <stdio.h>

int search(int arr[], int n, int num){
    static int ind = 0;
    if (arr[ind]==num) {
        return ind;
    }
    else{
        ind++;
        search(arr,n,num);
    }
    if(ind>=n){
        return -1;
    }
}

int main(){
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements of array: \n");
    for (int i =0;i<n; i++){
        scanf("%d", &arr[i]);
    }
    int num;
    printf("Enter num to check: ");
    scanf("%d", &num);
    int ans = search(arr,n,num);
    printf("Index of first occurrence of %d: %d (-1 => not present)\n", num, ans);

}
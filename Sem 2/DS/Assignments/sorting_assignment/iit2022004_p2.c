#include <stdio.h>

int main(){
    int n;
    printf("Enter value of n: ");
    scanf("%d", &n);
    int A[n];
    for (int i = 0; i<n; i++){
        scanf("%d", &A[i]);
    }
    int B[100];
    //initializing elements of B to 0;
    for (int i = 0; i<100; i++) B[i] = 0;
    //storing the count of each element in A, in B.
    for (int i = 0; i<n; i++){
        B[A[i]]++;
    }
    int index = 0;
    //sorting array A using counts stored in B
    for (int i = 0; i<100; i++){
        while (B[i] != 0){
            A[index] = i;
            index++;
            B[i]--;
        }
    }
    for (int i = 0; i<n; i++){
        printf("%d ", A[i]);
    }
}
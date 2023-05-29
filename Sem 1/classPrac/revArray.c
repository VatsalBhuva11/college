#include <stdio.h>
#include <printArr.h>

void revArray(int a[],int n){
    for(int i = 0; i < n/2; i++){
        int temp = a[i];
        a[i] = a[n-i-1];
        a[n-i-1] = temp;
    }
}

int main(){
    int a[100];
    int n;
    printf("Enter number of elements in array: ");
    scanf("%d", &n);
    printf("Enter elements of array: ");
    for (int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    printf("The array is: ");
    print1DArr(a,n);
    revArray(a,n);
    printf("Reversed array is: ");
    print1DArr(a,n);

}
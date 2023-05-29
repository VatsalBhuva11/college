#include <stdio.h>

int main(){
    int arr[50];
    arr[0] = 1;
    printf("%u\n", sizeof(arr)/sizeof(int));
}
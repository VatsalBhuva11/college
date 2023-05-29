#include <stdio.h>

int main(){
    int arr[][3] = {{1,2,3},{4,5,6},{7,8,9}};
    printf("%u\n",arr);
    printf("%u\n",arr+1);
    printf("%u\n",arr+2);
    printf("\n");
    printf("%u\n", *(arr));
    printf("%u\n", *(arr+1));
    printf("%u\n", *(arr+2));
    printf("--------------------------------------------------------------------------\n");
    int arr3[2][3][2] = { {{5, 10}, {6, 11}, {7, 12}}, {{20, 30}, {21, 31}, {22, 32}} };
    printf("%u\n", arr3);
    printf("%u\n", arr3+1);
    printf("\n");
    printf("%u\n", *arr3);
    printf("%u\n", *(arr3+1));
    printf("\n");
    printf("%u\n", *(*(arr3)+1));
    printf("\n");
    printf("%u\n", *(*(*(arr3)+1)+1));
}   
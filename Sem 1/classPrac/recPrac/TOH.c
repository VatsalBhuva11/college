#include <stdio.h>

void TOH(int n, char a, char b, char c);

int main(){
    int n;
    printf("Enter number of disks: ");
    scanf("%d", &n);
    TOH(n,'A','B','C');
}

void TOH(int n, char a, char b, char c){
    if (n>0){
        TOH(n-1,a,c,b);
        printf("Move disk %d from %c to %c\n",n,a,c);
        TOH(n-1,b,a,c);
    }
}
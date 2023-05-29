#include <stdio.h>

int countNum(int n){
    static int sum = 0;
    if (n<10){
        sum+=n;
        printf("Sum of digits: %d\n",sum);
        return 1;
    }
    sum+=n%10;
    return 1+countNum(n/10);
}

int main(){
    int n;
    printf("Enter number: ");
    scanf("%d",&n);
    int count = countNum(n);
    printf("Number of digits: %d\n",count);
}
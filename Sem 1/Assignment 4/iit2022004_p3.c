/*
Vatsal Bhuva IIT2022004 Assignment 4
*/
#include <stdio.h>

int main(){
    char c;
    int num;
    int sum = 0, count = 0;
    do{
        printf("Would you like to quit? (Enter 'q') : ");
        //space before c to capture the enter key
        scanf(" %c", &c);
        if (c == 'q') break;
        printf("Enter a number: ");
        scanf("%d", &num);
        printf("\n");
        sum += num; count += 1;
        
    } while(1);
    printf("Average of entered numbers is: %f",(float)sum/count);
}
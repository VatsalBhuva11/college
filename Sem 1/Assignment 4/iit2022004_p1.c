/*
Vatsal Bhuva IIT2022004 Assignment 4
*/
#include <stdio.h>

int main(){
    //print first 6 rows of the pattern
    for (int i = 1; i <= 6; i++){ 
        //print the spaces for each row
        for (int j = 0; j < 12-i*2; j++){
            printf(" ");
        }
        //print the stars for each row
        for (int j = 0; j<i;j++){
            printf("* ");
        }
        printf("\n");
    }
    //similar to above for loops
    for (int i = 1; i <= 6; i++){
        for (int j = 0; j<i*2;j++){
                printf(" ");
            }
        for (int j = 0; j<6-i;j++){
            printf("* ");
        }
        printf("\n");
    }
    
}

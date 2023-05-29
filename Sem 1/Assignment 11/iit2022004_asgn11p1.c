/*
VATSAL BHUVA
IIT2022004
Assignment 11 - Problem 1
*/
#include <stdio.h>
#include <stdlib.h>

int main(){
    
    FILE *ptr;
    ptr = fopen("ITP.txt","w");
    if (ptr == NULL){
        printf("Cannot open file.");
        exit(0);
    }
    fprintf(ptr, "Introduction to Programming\n");
    fclose(ptr);
    
return 0;
}
/*
VATSAL BHUVA
IIT2022004
Assignment 11 - Problem 3
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    
    FILE *ptr;
    ptr = fopen(argv[1], "r");
    if (argc != 2){
        printf("Enter in format: ./a.exe <filename>\n");
        exit(0);
    }
    if (ptr == NULL){
        printf("Cannot open file.\n");
        exit(0);
    }
    char line[1000];
    int count = 0;
    while (fgets(line, 1000, ptr)!=NULL){
        count++;
    }
    printf("Number of lines in file %s: %d",argv[1],count);
    
return 0;
}
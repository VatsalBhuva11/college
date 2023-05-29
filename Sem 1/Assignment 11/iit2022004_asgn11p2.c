/*
VATSAL BHUVA
IIT2022004
Assignment 11 - Problem 2
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    
    FILE *ptr;
    ptr = fopen(argv[1],"w+");
    if (argc != 2){
        printf("Enter in format: ./a.exe <filename>\n");
        exit(0);
    }
    if (ptr == NULL){
        printf("Cannot open file.\n");
        exit(0);
    }
    int i = 1;
    while(i<=5){
        fprintf(ptr, "Line number %d\n",i);
        i++;
    }


    fseek(ptr,0,SEEK_SET);
    char line[1000];
    printf("Contents of file are:\n");
    while(fgets(line, 1000, ptr)!=NULL){
        printf("%s", line);
    }

    fclose(ptr);


return 0;
}
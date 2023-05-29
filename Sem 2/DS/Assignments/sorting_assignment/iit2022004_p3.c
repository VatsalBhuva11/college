#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//gives the date in yymmdd format
char * interchange(char s[]){ 
    char *temp = (char *)malloc(10 * sizeof(char));
    int index = 0;
    for (int i = 6; i<10; i++) temp[index++] = s[i];
    for (int i = 3; i<5; i++) temp[index++] = s[i];
    for (int i = 0; i<2; i++) temp[index++] = s[i];
    return temp;
}

int main(){
    int n;
    printf("Enter number of dates: ");
    scanf("%d", &n);
    char *dates[n];
    printf("Enter dates in dd-mm-yyyy (including hiphens) format:\n");
    for (int i = 0; i<n; i++){
        dates[i] = (char *)malloc(sizeof(char)*10);
        scanf("%s", dates[i]);
    }
    char *temp = (char *)malloc(10 * sizeof(char));
    //bubble sort to sort the dates
    for (int i = 0; i<n-1; i++){
        for (int j = 0; j<n-i-1; j++){
            if (strcmp(interchange(dates[j]), interchange(dates[j+1])) > 0){
                strcpy(temp, dates[j]);
                strcpy(dates[j], dates[j+1]);
                strcpy(dates[j+1], temp);
            }
        }
    }
    printf("Dates in sorted order:\n");
    for (int i = 0; i<n; i++){
        printf("%s\n", dates[i]);
    }
}


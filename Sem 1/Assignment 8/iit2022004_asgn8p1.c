/*
VATSAL BHUVA
IIT2022004
Assignment 8 - Problem 1
*/

#include <stdio.h>

struct Marks{
    int rollno;
    char name[100];
    int chem_marks;
    int maths_marks;
    int phy_marks;
};

int main(){
    struct Marks students[5];
    for (int i = 0; i<5; i++){
        printf("Student %d: \n",i+1);
        printf("Enter roll no. : ");
        scanf("%d", &students[i].rollno);
        printf("Enter name : ");
        scanf("%s", &students[i].name);
        printf("Enter chem marks. (out of 100): ");
        scanf("%d", &students[i].chem_marks);
        printf("Enter maths marks. (out of 100): ");
        scanf("%d", &students[i].maths_marks);
        printf("Enter phy marks. (out of 100): ");
        scanf("%d", &students[i].phy_marks);
        printf("\n");
    }

    for (int i = 0; i<5; i++){
        float sum = 0;
        sum += students[i].chem_marks+students[i].maths_marks+students[i].phy_marks;
        printf("Average of Student %d is: %f%%\n", i+1, sum/3);
    }
}
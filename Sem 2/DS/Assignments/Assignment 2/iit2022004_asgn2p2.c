/*
Assignment 2 - Problem 3
Vatsal Bhuva
IIT2022004
*/
#include <stdio.h>

struct students{
    char name[20];
    int rollno;
    float cgpa;
};

int main(){
    
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);
    struct students arr[n];
    struct students maxCg, minCg;
    int highestCg = -__INT_MAX__;
    int lowestCg = __INT_MAX__;
    for (int i =0; i<n; i++){
        printf("Enter name of student %d: ",i+1);
        scanf("%s", arr[i].name);
        printf("Enter rollno of student %d: ",i+1);
        scanf("%d", &arr[i].rollno);
        printf("Enter cgpa of student %d: ",i+1);
        scanf("%f", &arr[i].cgpa);
        if (arr[i].cgpa > highestCg) {
            highestCg = arr[i].cgpa;
            maxCg = arr[i];
        }
        if (arr[i].cgpa < lowestCg) {
            lowestCg = arr[i].cgpa;
            minCg = arr[i];
        }
        printf("\n");
    }
    printf("Student details with highest CGPA:\n");
    printf("Name: %s\n",maxCg.name);
    printf("RollNo: %d\n",maxCg.rollno);
    printf("CGPA: %f\n",maxCg.cgpa);
    printf("\n");
    printf("Student details with lowest CGPA:\n");
    printf("Name: %s\n",minCg.name);
    printf("RollNo: %d\n",minCg.rollno);
    printf("CGPA: %f\n",minCg.cgpa);
    
    
return 0;
}
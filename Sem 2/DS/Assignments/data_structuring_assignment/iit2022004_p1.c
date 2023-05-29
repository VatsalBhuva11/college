#include <stdio.h>

struct student{
    int enrl_no;
    char name[50];
    char branch[10];
    float cgpa;
};

void printDets(struct student s){
    printf("Enrollment Number: %d\n", s.enrl_no);
    printf("Name: %s\n", s.name);
    printf("Branch: %s\n", s.branch);
    printf("CGPA: %f\n", s.cgpa);
    printf("\n");
}

int main(){
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);
    struct student students[n];
    for (int i = 0; i<n; i++){
        printf("Enter enrollment number: ");
        scanf("%d", &(students[i].enrl_no));
        printf("Enter name: ");
        scanf("%s", students[i].name);
        printf("Enter branch: ");
        scanf("%s", students[i].branch);
        printf("Enter cgpa: ");
        scanf("%f", &(students[i].cgpa));
        printf("\n");
    }
    int enrl_no;
    printf("Enter student's enrollment number to search for: ");
    scanf("%d", &enrl_no);
    int flag = 1;
    for (int i = 0; i<n; i++){
        if (students[i].enrl_no == enrl_no){
            printDets(students[i]);
            flag = 0;
            printf("\n");
            break;
        }
    }
    if (flag) printf("Invalid Enrollment number.\n");

    printf("Sorted based on enrollment numbers:\n");
    //bubble sort to sort the students based on their enrollment no.
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n-i-1; j++){
            if (students[j].enrl_no > students[j+1].enrl_no){
                struct student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }
    for (int i = 0; i<n; i++){
        printDets(students[i]);
    }

    printf("Enter student's enrollment number to search for: ");
    scanf("%d", &enrl_no);
    int low = 0, high = n; flag = 1;
    while (low <= high){
        int mid = low + (high - low)/2;
        if (students[mid].enrl_no == enrl_no){
            printDets(students[mid]);
            flag = 0;
            printf("\n");
            break;
        }
        else{
            if (enrl_no > students[mid].enrl_no) low = mid+1;
            else high = mid-1;
        }
    }
    if (flag) printf("Invalid Enrollment number entered.\n\n");
    printf("Sorted using Insertion sort in order of CGPA:\n");
    //insertion sort to sort based on CGPA
    for (int i = 0; i<n-1; i++){
        int j = i+1;
        while (j > 0){
            if (students[j].cgpa < students[j-1].cgpa){
                struct student temp = students[j];
                students[j] = students[j-1];
                students[j-1] = temp;
                j--;
            }
            else break;
        }
    }
    for (int i = 0; i<n; i++){
        printDets(students[i]);
    }   


}
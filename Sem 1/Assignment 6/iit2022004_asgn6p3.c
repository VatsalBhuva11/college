/*
VATSAL ASHVINBHAI BHUVA
IIT2022004
Assignment 6, Problem 3
*/

#include <stdio.h>
#include <ctype.h>

int get(int x, int db[][2]); 
int add(int x, int y, int db[][2], int *size);
float avg(int db[][2], int size);
void printArr(int db[][2], int size);

int main(){
    int db[100][2] ; //created a 2D array of the form {{id, marks}}
    int n, choice, id, marks;
    char flag; //flag to re-run the code depending on user input.
    printf("Enter number of students: ");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){ //take students as input.
        printf("Enter id and marks of student %d: ",i);
        scanf("%d %d", &db[i-1][0], &db[i-1][1]);

    }
    while (1){
        
        printf("Enter operation you want to perform:\n");
        printf("1. Get marks of student with id x\n");
        printf("2. Add student with id and marks to db\n");
        printf("3. Find average of marks of students\n");
        printf("Enter operation (1,2,3) : ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Enter id of student: ");
                scanf("%d",&id);
                printf("Marks of student with id %d is: %d\n",id,get(id, db));
                break;

            case 2:
                int marks;
                printf("Enter id of student: ");
                scanf("%d",&id);
                printf("Enter marks of student: ");
                scanf("%d",&marks);
                add(id, marks, db, &n);
                printf("New array containing students details: \n");
                printArr(db,n);
                break;
            
            case 3:
                printf("Average of marks of students is: %f\n",avg(db, n));
                break;
            
            default: printf("Invalid operation.");
        }
        printf("Would you like to continue (n to exit) : ");
        scanf(" %c", &flag);
        if (tolower(flag) == 'n'){
            break;
        }
        printf("\n");
    }
    

}

int get(int x, int db[][2]){ 
    for (int i = 0; i < 100; i++){
        if (db[i][0] == x){
            return(db[i][1]);
        }
    }
}

int add(int x, int y, int db[][2], int *size){
    db[*size][0] = x;
    db[*size][1] = y;
    (*size)++; //passing size as pointer to update the size of the array after adding new student.
}

float avg(int db[][2], int size){
    float sum = 0;
    for (int i = 0; i < size; i++){
        sum += db[i][1];
    }
    return sum/size;
}

void printArr(int db[][2], int size){
    for (int i = 1; i <= size; i++){
        printf("student %d: id = %d, marks = %d\n", i, db[i-1][0], db[i-1][1]);
    }
}
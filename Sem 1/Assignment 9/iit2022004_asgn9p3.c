/*
Vatsal Bhuva
IIT2022004
Assignment 9 - Problem 3
*/
#include <stdio.h>
#define ROWS 3
#define COLS 3

void matrixInput(int mat[][COLS]);
void matrixPrint(int mat[][COLS]);
void matrixAdd(int mat1[][COLS], int mat2[][COLS], int res[][COLS]);

int main(){
    int mat1[ROWS][COLS], mat2[ROWS][COLS], res[ROWS][COLS];
    printf("Enter matrix 1:\n");
    matrixInput(mat1);
    printf("Enter matrix 2:\n");
    matrixInput(mat2);
    printf("Matrix 1 is:\n");
    matrixPrint(mat1);
    printf("Matrix 2 is:\n");
    matrixPrint(mat2);
    printf("Sum of matrix 1 and matrix 2 is:\n");
    matrixAdd(mat1,mat2,res);
    matrixPrint(res);

}

void matrixInput(int mat[][COLS]){
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j<COLS; j++){
            printf("Enter element at (%d,%d): ",i,j);
            scanf("%d", *(mat+i)+j);
        }
    }
}
void matrixPrint(int mat[][COLS]){
    for (int i = 0; i<ROWS; i++){
        for (int j = 0; j<COLS; j++){
            printf("%d ", *(*(mat+i)+j));
        }
        printf("\n");
    }
}
void matrixAdd(int mat1[][COLS], int mat2[][COLS], int res[][COLS]){
    for (int i = 0; i<ROWS; i++){
        for (int j = 0; j<COLS; j++){
            *(*(res + i) + j) = *(*(mat1 + i) + j) + *(*(mat2 + i) + j);
        }
    }
}

#include <stdio.h>
/*
 * Implement Insertion sort
 * input data from file
 * output to file
 */

int main() {
    FILE *file = fopen("data.txt", "r");
    int array[10];
    int size = 0;
    while(fscanf(file, "%d", &array[size]) == 1) {
        size++;
    }
    file = fopen("data.txt", "a");

    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    for(int i = 1; i < size; i++)
    {
        int key = array[i];
        int j = i-1;
        while(j >= 0 && array[j] > key)
        {
            array[j+1] = array[j];
            j--;
        }
        
        array[j+1] = key;
    }
    fprintf(file,"\n");
    for (int i = 0; i < size; i++) {
        fprintf(file,"%d ", array[i]);
    }
    fclose(file);

}

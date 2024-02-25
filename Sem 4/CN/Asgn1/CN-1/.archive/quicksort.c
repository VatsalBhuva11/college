#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int l, int r)
{
    int pivot = l+rand()%(l-r);
    swap(arr+pivot, arr+r);
    pivot = arr[r];
    int pi = l;
    for (int i = l; i < r; i++)
    {
        if (arr[i] <= pivot)
        {
            swap(arr+i, arr+pi);
            pi++;
        }
    }
    
    swap(arr+pi, arr+r);
    return pi;
}

void quicksort(int arr[], int l, int r)
{
    if (l >= r)
        return;
    int pivot = partition(arr, l, r);
    quicksort(arr, 0, pivot-1);
    quicksort(arr, pivot+1, r);
}

int main()
{
    FILE *file = fopen("data.txt", "r");
    int n = 6;
    int array[n];
    int size = 0;
    while(fscanf(file, "%d", &array[size]) == 1) {
        size++;
    }
    

    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    quicksort(array, 0, n-1);   
    file = fopen("data.txt", "a");
    fprintf(file, "\n");
    for (int i = 0; i < n; i++)
    {
        fprintf(file,"%d ", array[i]);
    }
    fclose(file);
}

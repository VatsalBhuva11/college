#include <stdio.h>
#include <stdlib.h>
int n;
int *subset;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b; 
    *b = temp;
}

void printSubset(int *arr, int l){
    for (int i = 0; i<l; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

}

void permutations(int *subset, int l, int r, int len){
    if (l == r){
        printSubset(subset, len);
    }
    else{
        for (int i = l; i<=r; i++){
            swap(&subset[l], &subset[i]);
            permutations(subset, l+1, r, len);
            swap(&subset[l], &subset[i]);
        }
    }
}

void subset_generation(int **arr, int i, int *count, int r){
    if (i == n) {
        printSubset(subset, *count);
        // printSubset(subset, *count);
        if (*count == r){
            permutations(subset, 0, r-1, r);
        }
        return;
    }
    subset_generation(arr, i+1, *count,r ); 
    subset[(*count)]=*((*arr)+i);
    (*count)++;
    subset_generation(arr, i+1, *count,r );
    // (*count)--;

}
int main(){
    printf("Enter size of array: ");
    scanf("%d", &n);
    subset = (int *)calloc(n,sizeof(int));
    int *arr = (int *)malloc(sizeof(int)*n);
    printf("Enter elements:\n");
    for (int i = 0; i<n; i++){
        scanf("%d", arr+i);
    }
    int r; int count = 0;
    printf("Enter number of elements in subsets: ");
    scanf("%d", &r);
    subset_generation(&arr, 0, &count, r);
}
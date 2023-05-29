#include <stdio.h>

int maxi(int i, int j){
    if (i>j) return i;
    return j;
}

int main(){
    int n;
    printf("Enter number of elements in array: ");
    scanf("%d", &n);
    int arr[100];
    for (int i = n; i<=2*n-1; i++){
        scanf("%d", &arr[i]);
    }
    for (int i = 2*n-2; i>1; i-=2){
        if (arr[i] >= arr[i+1]) arr[i/2] = arr[i];
        else arr[i/2] = arr[i+1];
    }
    int max = arr[1];
    printf("MAX: %d\n", max);
    arr[1] = -1;
    //downward traversal to reduce the max to calculate the next max
    int max_indices_array[100];
    int index = 0; int compared; int count = 0;
    for (int i = 1; i<=2*n-1;){
        if (arr[2*i] == max) {
            arr[2*i] = -1;
            compared = arr[2*i+1];
            i = 2*i;
        }
        else {
            arr[2*i + 1] = -1;
            i = 2*i + 1;
            compared = arr[2*i];
        }
        printf("%d ", compared);
        max_indices_array[index++] = i;
        max_indices_array[index++] = compared; 
        count+=2;
    }
    //upward traversal
    int curMax = max_indices_array[0];
    for (int i = count-2; i>=0; i-=2){
        if (i == count-2) {
            arr[max_indices_array[i]] = max_indices_array[i+1];
            curMax = max_indices_array[i+1];
        }
        else max_indices_array[i-2] = maxi(curMax, arr[i+1]);
    }

    int next_max = arr[2];
    printf("NEXT MAX: %d\n", next_max);

}
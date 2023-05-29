#include <stdio.h>

int binSearch(int arr[], int low, int high, int element){
    int mid = (low+high)/2;
    if (arr[mid] == element){
        return mid;
    }
    else{
        if (low > high) return -1;
        if (arr[mid] > element) return binSearch(arr, low, mid-1, element);
        else return binSearch(arr, mid+1, high, element);
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i<n; i++){
        scanf("%d", arr+i);
    }
    int num;
    printf("Enter element to search: ");
    scanf("%d", &num);
    int pos = binSearch(arr, 0, n, num);
    if (pos == -1) printf("Element is not present in the array\n");
    else printf("Element is present at the position: %d\n",pos);
    
}
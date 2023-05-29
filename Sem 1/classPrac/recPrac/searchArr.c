#include <stdio.h>

int search(int arr[], int n, int num){
    static int ind = 0;
    if (arr[ind] == num){
        return ind;
    }
    else{
        ind++;
        if (ind==n){
            return -1;
        }
        search(arr,n,num);
    }
}

int main(){
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements of array: \n");
    for (int i = 0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    int num;
    printf("Enter number to search: ");
    scanf("%d", &num);
    int ans = search(arr, n, num);
    if (ans == -1) printf("%d is not present in the array.\n",num);
    else{
        printf("First occurrence of %d in array is at index %d\n",num,ans);
    }

}
#include <stdio.h>

int sum(int arr[], int n){
    int ans = 0;
    for (int i = 0 ; i<n; i++){
        ans+=arr[i];
    }
    return ans;
}

int dp[10000][10000];

int subset_sum(int index, int sum, int arr[]){
    if (sum == 0) return 1; //if required sum is already met.
    if (index < 0) return 0; //if required sum is not met, but all elements over
    if (dp[index][sum] != -1) return dp[index][sum];
    //do not consider the ith element.
    int ans = subset_sum(index-1, sum, arr);
    //consider the ith element. if either of the sums are equal, return true (done using or)
    if (sum - arr[index] >= 0){
        ans = ans | subset_sum(index-1, sum-arr[index], arr);
    }
    return dp[index][sum] = ans;
}

int main(){
    int n, sum;
    scanf("%d %d", &n, &sum);
    int arr[n];
    for (int i = 0 ; i < n; i++){
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i<10000; i++){
        for (int j = 0; j<10000; j++) dp[i][j] = -1;
    }
    int ans = subset_sum(n-1, sum, arr);
    if (ans) printf("Subset sum exists\n");
    else printf("Subset sum doesn't exist.\n");
}
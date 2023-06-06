#include <stdio.h>

int max(int a, int b){
    if(a>b) return a;
    return b;
}

int wt[105], val[105];
long long dp[105][100005];

//index of current item being processed, amount of weight that can be added.
int knapsack(int index, int amount){
    if (index < 0) return 0;
    if (amount < 0) return 0;
    //not considering the index th element
    int ans = knapsack(index - 1, amount);

    //consider the current element
    if (amount - wt[index] >= 0){
        //max because for a given element, it is possible that not including that element can
        //give a higher sum as it's weight equivalent would have a higher price.
        ans = max(ans, knapsack(index-1, amount-wt[index])+ val[index]);
    }
    return ans;
}

int main(){
    int n, w;
    printf("Enter number of items, and max weight: ");
    scanf("%d %d", &n, &w);
    for (int i = 0; i<n; i++){
        scanf("%d %d", &wt[i], &val[i]);
    }
    for (int i = 0; i<105; i++){
        for (int j = 0; j<100005; j++){
            dp[i][j] = -1;
        }
    }

    printf("Max possible price: %d\n", knapsack(n, w));

}
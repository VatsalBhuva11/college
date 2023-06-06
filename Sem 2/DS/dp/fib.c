#include <stdio.h>
int n;
int dp[10000];

int fib(int n){
    if (n<2) return n;
    if (dp[n] != -1) return dp[n]; //memoisation
    return dp[n] = fib(n-1) + fib(n-2);
}


int main(){
    printf("Enter value of n: ");
    scanf("%d", &n);

    for (int i = 0; i < 10000; i++){
        dp[i] = -1;
    }
    for (int i= 1; i<=n; i++){
        int ans = fib(i);
        printf("%d ",ans);
    }

}
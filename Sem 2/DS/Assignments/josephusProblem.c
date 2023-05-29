#include <stdio.h>

int josephusProblem(int n, int k){
    if (n==1) return 0;
    else{
        return (josephusProblem(n-1, k)+k)%n;
    }
}

int main(){
    printf("Enter number of people: ");
    int n;
    scanf("%d", &n);
    int k;
    printf("Enter step count: ");
    scanf("%d", &k);
    int ans = josephusProblem(n,k);
    printf("Person at position %d survives\n", ans+1); //1-based indexing
}
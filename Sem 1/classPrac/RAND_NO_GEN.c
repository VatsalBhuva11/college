#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int n;
    srand(time(0));
    scanf("%d",&n);
    
    printf("%d random numbers are: \n",n);
    for (int i = 0; i<n; i++){
        printf("%d\n",(1+rand()%6)); //generates rand no. bw 1 and 6.
    }
}
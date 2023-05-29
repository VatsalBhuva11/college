#include <stdio.h>

int sum(int x){
    if (x==1) return 1;
    else{
        return (x+sum(--x));
    }
}
int main(){
    printf("%d\n",sum(5));
}
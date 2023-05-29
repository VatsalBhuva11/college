#include <stdio.h>
#include <string.h>

void rev(char a[],int n){
    if (n>0){
        printf("%c",a[n-1]);
        rev(a,n-1);
    }
    return;
}

int main(){
    char s[10000];
    printf("Enter string: ");
    fgets(s,10000,stdin);
    int len = strlen(s);
    printf("Reversed string: ");
    rev(s,len-1);
}
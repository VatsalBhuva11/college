#include <stdio.h>
#include <string.h>

void swap(char *a, char *b){
    char temp[100];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

int main(){
    int n;
    scanf("%d", &n);
    char arr[n][100];
    for (int i = 0; i<n; i++){
        scanf("%s", arr[i]);
    }
    for (int i = 0; i<n-1; i++){
        for (int j = i+1; j<n; j++){
            if (strcmp(arr[i],arr[j]) > 0){
                swap(arr[i], arr[j]);
            }
        }
    }
    for (int i =0; i<n; i++){
        printf("%s ", arr[i]);
    }
}
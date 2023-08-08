#include <stdio.h>

int *nfa[4][2][10] = 
{
    {{1}, {2}},
    {{1,3}, {1}},
    {{2}, {2,3}},
    {{__INT32_MAX__}, {__INT32_MAX__}}
};

int main(){

    for (int i = 0; i<4; i++){
        for (int j = 0; j<2; j++){
            printf("%d ", nfa[i][j][0]);
        }
        printf("\n");
    }
    
return 0;
}
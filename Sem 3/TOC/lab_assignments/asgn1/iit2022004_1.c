#include <stdio.h>
#include <string.h>
#define MAX 1000

int transitionMatrix[MAX][MAX];
int finalStates[MAX];
int m,n, noOfFinalStates;

int dfa(int dfa[MAX][MAX], char s[1000]){
    int len = strlen(s);
    int state = 0;
    for (int i = 0; i<len; i++){
        char curr = s[i];        
        state = dfa[state][curr-'a'];
        printf("%d -> ", state);
    }
    for (int i = 0; i<noOfFinalStates; i++){
        if (finalStates[i] == state){
            return 1;
        }
    }
    return 0;
}

int main(){
    printf("Enter string: ");
    char s[1000];
    scanf("%s", s);
    printf("Enter number of states and symbols: ");
    scanf("%d %d", &m, &n);

    printf("Enter states in transition matrix:\n");
    for (int i = 0; i<m; i++){
        for (int j = 0; j<n; j++){
            printf("Enter state at (%d, %d): ", i, j);
            scanf("%d", &transitionMatrix[i][j]);
        }
    }

    printf("\nEnter no. of final states: ");
    scanf("%d", &noOfFinalStates);
    for (int i = 0; i<noOfFinalStates; i++) scanf("%d", &finalStates[i]);

    int ans = dfa(transitionMatrix, s);
    if (ans) printf("Accepted\n");
    else printf("Not accepted\n");

return 0;
}
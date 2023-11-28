//IIT2022004

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter no of states: ");
    scanf("%d", &n);
    
    // Defining an array for epsilon closure of states
    int **epsicol = (int **)malloc(n * sizeof(int *));
    int no_of_states_epsicol[n];

    for (int i = 0; i < n; i++) {
        printf("Enter no of states which can be reached through epsilon from q%d: ", i);
        scanf("%d", &no_of_states_epsicol[i]);
        
        epsicol[i] = (int *)malloc(no_of_states_epsicol[i] * sizeof(int));
        for (int j = 0; j < no_of_states_epsicol[i]; j++) {
            scanf("%d", &epsicol[i][j]);
        }
    }

    int s;
    printf("Enter no of symbols in your language: ");
    scanf("%d", &s);

    // Defining the NFA transition table
    int ***nfa = (int ***)malloc(n * sizeof(int **));
    //n is number of states
    //s is number of symbols
    int nfa_states[n][s];

    for (int i = 0; i < n; i++) {
        nfa[i] = (int **)malloc(s * sizeof(int *));
        for (int j = 0; j < s; j++) {
            printf("Enter no of states of %d symbol through q%d: ", j + 1, i);
            //how many output states for each symbol, for each state stored in 2D array nfa_states
            scanf("%d", &nfa_states[i][j]);

            nfa[i][j] = (int *)malloc(nfa_states[i][j] * sizeof(int));
            for (int k = 0; k < nfa_states[i][j]; k++) {
                //get output states for each input, for each state.
                printf("Enter %d state from q%d through %d symbol: ", k + 1, i, j + 1);
                scanf("%d", &nfa[i][j][k]);
            }
        }
    }

    // Array for final states
    int num;
    printf("Enter no of final states: ");
    scanf("%d", &num);
    int final[num];

    for (int i = 0; i < num; i++) {
        printf("Enter %d final state: ", i + 1);
        scanf("%d", &final[i]);
    }

    int prev_states[n];
    int cur_states[n];
    //no_of_states_epsicol[i] stores the number of states that can be reached by epsilon.
    //epsicol[i][j] is the jth state that can be reached by epsilon, from the ith states
    for (int i = 0; i < no_of_states_epsicol[0]; i++)
        prev_states[epsicol[0][i]] = 1;

    int len;
    printf("Enter length of your string: ");
    scanf("%d", &len);
    char *st = malloc(sizeof(char) * (len + 1));
    printf("Enter your string: ");
    scanf("%s", st);

    for (int i = 0; i < len; i++) {
        int ind = st[i] - 'a';
        for (int j = 0; j < n; j++) {
            if (prev_states[j] == 1) {
                for (int k = 0; k < nfa_states[j][ind]; k++) {
                    for (int l = 0; l < no_of_states_epsicol[nfa[j][ind][k]]; l++) {
                        cur_states[epsicol[nfa[j][ind][k]][l]] = 1;
                    }
                }
            }
        }
        for (int m = 0; m < n; m++) {
            prev_states[m] = cur_states[m];
            cur_states[m] = 0;
        }
    }
    
    int flag = 0;
    for (int i = 0; i < num; i++) {
        if (prev_states[final[i]] == 1)
            flag = 1;
    }

    if (flag == 1)
        printf("Accepted\n");
    else
        printf("Rejected\n");

    // Free dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(epsicol[i]);
        for (int j = 0; j < s; j++) {
            free(nfa[i][j]);
        }
        free(nfa[i]);
    }
    free(st);
    
    return 0;
}
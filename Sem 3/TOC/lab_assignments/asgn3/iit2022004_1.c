#include <stdio.h>
#include <stdlib.h>


struct e_nfa{
    int q;
    int a[3];
    int b[3];
    int E[3];

};
struct e_nfa states[3];

void setDefault(struct e_nfa *state){
    for (int i = 0; i<3; i++){
        state->a[i] = -1;
    }
    for (int i = 0; i<3; i++){
        state->b[i] = -1;
    }
    for (int i = 0; i<3; i++){
        state->E[i] = -1;
    }
}

void input(struct e_nfa states[]){
    for (int i = 0; i<3; i++){ //access structure from array of structures.
        printf("State %d:\n", i);
        setDefault(&states[i]);
        states[i].q = i; 
        for (int j = 0; j<3; j++){ //access input 'a','b','e'
            int num;
            scanf("%d", &(num));
            if (num == -1) break;
            else states[i].a[j] = num;
        }
        printf("\n");
        for (int j = 0; j<3; j++){
            int num;
            scanf("%d", &(num));
            if (num == -1) break;
            else states[i].b[j] = num;
        }
        printf("\n");
        for (int j = 0; j<3; j++){
            int num;
            scanf("%d", &(num));
            if (num == -1) break;
            else states[i].E[j] = num;
        }
        printf("\n");
    }
}

void print(struct e_nfa states[]){
    for (int i = 0; i<3; i++){ //access structure from array of structures.
        for (int j = 0; j<3; j++){ //access input 'a','b','e'
            printf("%d ", (states[i].a[j]));
        }
        printf("\n");
        for (int j = 0; j<3; j++){
            printf("%d ", (states[i].b[j]));
        }
        for (int j = 0; j<3; j++){
            printf("%d ", (states[i].E[j]));
        }
        printf("\n");
    }
}

int main(){
    
    input(states);

    printf("Epsilon closures:\n");

    for (int i = 0; i<3; i++){
        printf("State %d: ", states[i].q);
        for (int j = 0; j<3; j++){
            if (states[i].E[j] != -1){
                printf("%d ", states[i].E[j]);
            }
        }
        printf("\n");
    }

return 0;
}
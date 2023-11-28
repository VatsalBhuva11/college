//1
#include <stdio.h>
#include <string.h>

int dfa[3][2] = {
    {1, 0},
    {2, 0},
    {2, 2}
};

int main(){
    char s[100];
    scanf("%s", s);

    int len = strlen(s);
    int state = 0;

    for (int i = 0; i<len; i++){
        char curr = s[i];        
        state = dfa[state][curr-'a'];
        printf("%d -> ", state);
    }
    if (state == 2) printf("Accepted\n");
    else printf("Not accepted\n");

return 0;
}


//2
/*
#include <stdio.h>
#include <string.h>

int dfa[3][2] = {
    {1, 0},
    {2, 0},
    {2, 0}
};

int main(){
    char s[100];
    scanf("%s", s);

    int len = strlen(s);
    int state = 0;

    for (int i = 0; i<len; i++){
        char curr = s[i];        
        state = dfa[state][curr-'a'];
        printf("%d -> ", state);
    }
    // printf("%d\n", state);
    if (state == 2) printf("Accepted\n");
    else printf("Not accepted\n");

return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

struct lifo{
    char st[MAXSIZE];
    int top;
};
typedef struct lifo stack;

void push(stack *s, char brack){
    if (s->top == MAXSIZE-1){
        printf("Stack overflow\n");
        exit(-1);
    }
    else{
        (s->st)[(s->top)+1] = brack;
        (s->top)++;
    }
}

char pop(stack *s){
    if (s->top == -1){
        printf("Stack underflow (Unbalanced)\n");
        exit(-1);
    }
    else{
        char last = (s->st)[s->top];
        (s->top)--;
        return last;
    }
}

void printStack(stack *s){
    for (int i = 0; i<=(s->top); i++){
        printf("%c ", (s->st)[i]);
    }
    printf("\n");
}

int main(){
    stack *s = (stack *)malloc(sizeof(stack));
    s->top = -1;
    printf("Enter string of brackets: ");
    char brackets[MAXSIZE];
    scanf("%s", brackets);
    int flag = 0;
    for (int i = 0; i<strlen(brackets); i++){
        if (brackets[i]=='(' || brackets[i]=='{' || brackets[i]=='['){
            push(s, brackets[i]);
        }
        else{
            char r = pop(s);
            if (r=='{'&&brackets[i]!='}' || r=='('&&brackets[i]!=')' || r=='['&&brackets[i]!=']'){
                flag = 1;
                printf("Unbalanced\n");
                break;
            }
        }
        printStack(s);
    }
    if (flag == 0){
        if (s->top == -1){
            printf("Balanced\n");
        }
        else{
            printf("Unbalanced\n");
        }
    }


}
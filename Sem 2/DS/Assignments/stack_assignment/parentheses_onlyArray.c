#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100

void push(char stack[], int *top, char brack){
    if (*top == MAXSIZE){
        printf("Stack overflow\n");
        exit(-1);
    }
    else{
        *top = *top + 1;
        stack[*top] = brack;
    }
}

char pop(char stack[], int *top){
    if (*top == -1){
        printf("Stack Underflow\n");
        exit(-1);
    }
    else{
        char last = stack[*top];
        (*top)--;
        return last;
    }
}

void printStack(char stack[], int top){
    for (int i = 0; i<=top; i++){
        printf("%c ",stack[i]);
    }
    printf("\n");
}

int main(){
    char stack[MAXSIZE];
    char brackets[MAXSIZE]; int top = -1;
    printf("Enter string of brackets: ");
    scanf("%s",brackets);
    int flag = 1;
    for (int i = 0; i<strlen(brackets); i++){
        if (brackets[i]=='(' || brackets[i]=='[' || brackets[i]=='{'){
            push(stack, &top, brackets[i]);
        }
        else{
            char last = pop(stack, &top);
            if (last=='('&&brackets[i]!=')' || last=='{'&&brackets[i]!='}' || last=='['&&brackets[i]!=']'){
                printf("Unbalanced\n");
                flag = 0;
                break;
            }
        }
        printStack(stack,top);
    }
    if (flag){
        if (top == -1) printf("Balanced\n");
        else printf("Unbalanced\n");
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100

struct node{
    float st[MAXSIZE];
    int top;
};
typedef struct node stack;

void push(stack *s, int element){
    if (s->top == MAXSIZE){
        printf("Stack Overflow\n");
        exit(-1); 
    }
    else{
        (s->top)++;
        (s->st)[s->top] = element;
    }
}

int pop(stack *s){
    if (s->top == -1){
        printf("Stack Underflow\n");
        exit(-1);
    }
    else{
        int end = (s->st)[s->top];
        (s->top)--;
        return end;
    }
}

float calc(int a, int b, char op){
    if (op =='+'){
        return a + b;
    }
    else if (op =='-'){
        return a - b;
    }
    else if (op =='/'){
        if (b==0){
            printf("Division by zero error\n");
            exit(-1);
        }
        return (float)a / b;
    }
    else if (op =='*'){
        return a * b;
    }
}

void printStack(stack *s){
    for (int i = 0; i<=(s->top); i++){
        printf("%c ", (s->st)[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    stack *s = (stack *)malloc(sizeof(stack));
    s->top = -1;
    FILE *f = fopen(argv[1], "r");
    if (f == NULL){
        printf("File could not be opened\n");
        exit(-1);
    }
    char prefix[MAXSIZE];
    while (fgets(prefix, 100, f) != NULL){
        printf("%s", prefix);
        float ans = 0;
        for (int i = strlen(prefix)-2; i>=0; i--){
            if (prefix[i]>='0'&&prefix[i]<='9') push(s, prefix[i]-'0');
            else{
                int a = pop(s);
                int b = pop(s);
                int curr = calc(a,b,prefix[i]);
                push(s,curr);
            }
        }
        printf("Answer = %.2f\n", (s->st)[0]);
        pop(s);
        printf("\n");
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct temp{
    char data;
    struct temp *left;
    struct temp *right;
} tree;

typedef struct node{
    int top;
    tree *st[100];
}stack;

int isOperator(char c){
    if (c == '+' || c == '/' || c=='-' || c=='*') return 1;
    return 0;
}

void postorder(tree *node){
    if (node == NULL) return;
    else{
        postorder(node->left);
        postorder(node->right);
        printf("%c ", node->data);
    }
}
void inorder(tree *node){
    if (node == NULL) return;
    else{
        printf("%c ", node->data);
        postorder(node->left);
        postorder(node->right);
    }
}

int main(){
    char prefix[100];
    printf("Enter prefix expression: ");
    scanf("%s", prefix);
    stack *s;
    s = (stack *)malloc(sizeof(stack)); s->top = 0;
    
    for (int i = strlen(prefix)-1; i>=0; i--){
        tree *temp = (tree *)malloc(sizeof(tree));
        temp->data = prefix[i]; temp->right = NULL; temp->right = NULL;
        if (!isOperator(prefix[i])){
            (s->st)[s->top] = temp;
            (s->top)++;
        }
        else{
            (s->top)--;
            temp->left = (s->st)[s->top]; 
            (s->top)--;
            temp->right = (s->st)[s->top]; 
            (s->st)[s->top] = temp;   
            postorder((s->st)[s->top]); printf("\n");
            (s->top)++;         
        }
    }


}
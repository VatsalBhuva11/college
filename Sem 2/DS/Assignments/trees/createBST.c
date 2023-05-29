#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node{
    int data;
    struct tree_node *left, *right;
} node;
typedef node *tree;

tree create(tree root, int data){
    if (root == NULL){
        root = (tree)malloc(sizeof(node));
        root->data = data;
        root->left = root->right = NULL;
        return root;
    }
    else{
        if (data < root->data) create(root->left, data);
        else create(root->right, data);
        return root;
    }
}


int main(){
    int n;
    printf("Enter no. of nodes in BST: ");
    scanf("%d", &n);
    tree root = NULL;
    for (int i = 0; i<n; i++){
        int data;
        printf("Enter data: ");
        scanf("%d", &data);
        root = create(root, data);
    }
}
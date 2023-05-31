#include <stdio.h>
#include <stdlib.h>

int n;

typedef struct node{
    int data;
    struct node *left, *right;
} tree_node;
typedef tree_node *tree;

tree insert(tree root, int data){
    if (root == NULL){
        root = (tree)malloc(sizeof(tree_node));
        root->data = data;
        root->left = root->right = NULL;
        return root;
    }
    else{
        if (data < root->data){
            root->left = insert(root->left, data);
        }
        else{
            root->right = insert(root->right, data);
        }
        return root;
    }
}

void inorder(tree root){
    if (root == NULL) return;
    else{
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int height(tree root){
    
}

int main(){
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    tree root = (tree)malloc(sizeof(tree_node));
    root = NULL;
    for (int i = 0; i<n; i++){
        int data;
        printf("Enter data to insert: ");
        scanf("%d", &data);
        root = insert(root, data);
    }
    inorder(root);

}
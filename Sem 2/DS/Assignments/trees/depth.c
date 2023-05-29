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
        if (data < root->data) root->left = create(root->left, data);
        else root->right = create(root->right, data);
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

void inorderDepth(tree root, int count, int *max){
    if (root == NULL) return;
    else{
        inorderDepth(root->left, count+1, max);
        if (count > *max) *max = count;
        inorderDepth(root->right, count+1, max);
        if (count > *max) *max = count;
    }
}

int main(){
    printf("Enter number of nodes: ");
    int n; scanf("%d", &n);
    tree root = NULL;
    for (int i = 0; i<n; i++){
        int data;
        printf("Enter data: ");
        scanf("%d", &data);
        root = create(root, data);
    }
    printf("BST using inorder traversal: ");
    inorder(root); printf("\n");
    int max = -__INT_MAX__;
    inorderDepth(root,0, &max);
    printf("Depth of BST using inorder traversal: %d\n", max);

}
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
} tree;

void create(tree *node){
    tree *temp = node;
    
    int data;
    printf("Enter data: ");
    scanf("%d", &data);
    temp->data = data;

    int choice;
    tree *right = (tree *)malloc(sizeof(tree));
    tree *left = (tree *)malloc(sizeof(tree));
    node->right = right;
    node->left = left;
    printf("Do you want a left node of %d? (1 for yes, 0 for no): ", node->data);
    scanf("%d", &choice);
    if (choice == 1)create(left);
    else node->left = NULL;

    printf("Do you want a right node of %d? (1 for yes, 0 for no): ", node->data);
    scanf("%d", &choice);

    if (choice == 1) create(right);
    else node->right = NULL;

}

void preorder(tree *node){
    if (node == NULL) return;
    else{
        printf("%d ", node->data);
        preorder(node->left);
        preorder(node->right);
    }
}

void inorder(tree *node){
    if (node == NULL) return;
    else{
        inorder(node->left);
        printf("%d ", node->data);
        inorder(node->right);
    }
}
void postorder(tree *node){
    if (node == NULL) return;
    else{
        postorder(node->left);
        postorder(node->right);
        printf("%d ", node->data);
    }
}


int main(){
    
    tree *root = (tree *)malloc(sizeof(tree));    
    root->right = root->left = NULL;
    create(root);
    printf("Preorder traversal: ");
    preorder(root); printf("\n");
    printf("Inorder traversal: ");
    inorder(root); printf("\n");
    printf("Postorder traversal: ");
    postorder(root); printf("\n");

}
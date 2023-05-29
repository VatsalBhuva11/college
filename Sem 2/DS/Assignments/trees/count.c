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
        root->left = root->right = NULL;
        root->data = data;
        return root;
    }
    else{
        if (data < root->data){
            root->left = create(root->left, data);
        }
        else if(data > root->data){
            root->right = create(root->right, data);
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

int inorderCount(tree root){
    if (root == NULL) return 0;
    else{
        return inorderCount(root->left) + 1 + inorderCount(root->right);
    }
}

int main(){
    int n;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    tree root = NULL;
    for (int i = 0; i<n; i++){
        int data;
        printf("Enter data: ");
        scanf("%d", &data);
        root = create(root, data);
    }

    printf("Inorder traversal of BST: ");
    inorder(root); printf("\n");
    printf("Count using inorder traversal: %d\n", inorderCount(root));

}


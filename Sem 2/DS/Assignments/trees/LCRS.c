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

void LCRS(tree root){
    if (root == NULL) return;
    if (root->left != NULL){
        root->left = root->left; //left remains unchanged
        LCRS(root->left);
        root->left->right = root->right; //update right of left child after running LCRS on left child
        if (root->right != NULL){ //if right child is not null, have to recurse through right as well
            LCRS(root->right);
        }
        root->right = NULL; //make right child null by default, will be updated if sibling exists in backtracking
    }
    else if(root->right != NULL){
        root->left = root->right; //make right child as the left child;
        LCRS(root->left); //recurse through the right child in original BST.
        //recursing through left or right child gives same result as root->left = root->right and so, any change made in one will be seen in other since both POINT to same address of node
        root->left->right = NULL; //root->right can never have a sibling
        root->right = NULL; //while backtracking, make the right of the root as NULL. if sibling present, it get's updated.
    }
}

void lcrsTraversal(tree root){
    if (root == NULL) return;
    else{
        lcrsTraversal(root->left);
        printf("%d ", root->data);
        lcrsTraversal(root->right);
    }
}

void postorder(tree root){
    if (root == NULL) return;
    else{
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
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
    printf("Original BST using postorder traversal:\n");
    postorder(root); printf("\n\n");
    tree lcrs = (tree)malloc(sizeof(tree));
    lcrs = root;
    LCRS(lcrs);
    printf("LCRS traversal (inorder traversal):\n");
    lcrsTraversal(lcrs); printf("\n");
    

}
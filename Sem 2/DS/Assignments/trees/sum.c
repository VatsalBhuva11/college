#include <stdio.h>
#include <stdlib.h>

typedef struct temp{
    int data;
    struct temp *left, *right;
} node;
typedef node *tree;

tree create(tree root, int data){
    if (root == NULL){
        tree new = (tree)malloc(sizeof(node));
        new->data = data;
        new->left = new->right = NULL;
        return new;
    }
    else{
        if (data < root->data){
            root->left = create(root->left, data);
        }
        else{
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

int inorderSum(tree root, int sum){
    if (root == NULL) return 0;
    else{
        sum += inorderSum(root->left, 0);
        sum += root->data;
        sum += inorderSum(root->right, 0);
        return sum;
    }
}

int preorderSum(tree root, int sum){
    if (root == NULL) return 0;
    else{
        sum += root->data;
        sum += inorderSum(root->left, 0);
        sum += inorderSum(root->right, 0);
        return sum;
    }
}

int postorderSum(tree root, int sum){
    if (root == NULL) return 0;
    else{
        sum += root->data;
        sum += inorderSum(root->left, 0);
        sum += inorderSum(root->right, 0);
        return sum;
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
    printf("BST printed using inorder traversal: ");
    inorder(root);
    printf("\n");
    int ans = inorderSum(root, 0);
    printf("BST sum using inorder traversal: %d\n", ans);
}
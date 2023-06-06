#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *left, *right;
};
typedef struct node *tree;

tree insert(tree root, int data){
    if (root == NULL){
        tree new = (tree)malloc(sizeof(struct node));
        new->data = data;
        new->left = new->right = NULL;
        return new;
    }
    else{
        if (data < root->data){
            root->left = insert(root->left, data);
        }
        else root->right = insert(root->right, data);
        return root;
    }
}

tree delete(tree *root, int data){
    if (data < (*root)->data){
        return delete(&((*root)->left), data);
    }
    else if (data > (*root)->data){
        return delete(&((*root)->right), data);
    }
    else{
        if (*root == NULL) return NULL;
        else{ //found the node such that node->data = data
            tree deleted = *root;
            if ((*root)->right == NULL && (*root)->left == NULL){
                *root = NULL;
                return deleted;
            }
            else if((*root)->left == NULL){
                *root = (*root)->right;
                return deleted;
            } 
            else{
                tree parent = (*root)->left, temp = (*root)->left;
                while (temp->right != NULL){
                    parent = temp;
                    temp = temp->right;
                }
                (*root)->data = temp->data;
                if (temp == parent){ //if no right subtree of left child
                    (*root)->left = temp->left;
                    return deleted;
                }
                else{
                    parent->right = NULL;
                    return deleted;
                }
            }
                
        }
    }
}

void preorder(tree root){
    if (root == NULL) return;
    else{
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(tree root){
    if (root == NULL){
        return;
    }
    else{
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main(){
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    // tree root = (tree)malloc(sizeof(struct node));
    tree root = NULL;
    for (int i = 0; i<n; i++){
        int num;
        printf("Enter data: ");
        scanf("%d", &num);
        root = insert(root, num);
    }
    inorder(root);  printf("\n");
    int num;
    printf("Enter element to delete: ");
    scanf("%d", &num);
    tree deleted = delete(&root, num);
    //note: deleted->data now contains the data of the replaced node
    printf("inorder tree after deleting %d: ",num);
    inorder(root); printf("\n");
    printf("Enter element to insert: ");
    scanf("%d", &num);
    root = insert(root, num);
    printf("inorder tree after inserting %d: ",num);
    inorder(root); printf("\n");

}
#include <stdio.h>
#include <stdlib.h>

int n;

typedef struct node_tree{
    int data;
    struct node_tree *left, *right;
} node;
typedef node *tree;


void insert(tree (*root), int data){
    if ((*root) == NULL){
        (*root) = (tree)malloc(sizeof(node));
        (*root)->left = (*root)->right = NULL;
        (*root)->data = data;
    }
    else{
        if (data < (*root)->data){
            insert(&((*root)->left), data);
        }
        else{
            insert(&((*root)->right), data);
        }
    }
}

tree delete(tree *root, int data){
    if (*root == NULL) return NULL; //if element not present in the BST
    //recurse to find the element to delete.
    if (data < (*root)->data){
        return delete(&((*root)->left), data);
    }
    else if(data > (*root)->data){
        return delete(&((*root)->right), data);
    }
    //when node to delete has been found
    else{ 
      
        tree temp = *root;
        if (temp->right == NULL && temp->left == NULL) { //if leaf node deleted
            *root = NULL;
        } 
        else if(temp->left == NULL){ //change root to the minimum in the right subtree.
            (*root) = (*root)->right;
        }
        else{
            //when temp->left is NOT NULL (temp->right can be NULL)
            tree node = temp->left;
            tree parent = node;
            while (node->right != NULL){
                parent = node;
                node = node->right;
            }
            (*root)->data = node->data;
            if (parent == node){ //only happens when temp->right is NULL as while loop doesn't run
                //in this case, the node is replaced by the left subtree of node
                (*root)->left = node->left;
            }
            else if (node->left != NULL){
                parent->right = node->left; //if replacing node has a left subtree
            }
            else{
                parent->right = NULL;
            }
        }
        return temp;
    
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

void preorder(tree root){
    if (root == NULL) return;
    else{
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

int main(){
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    tree root = (tree) malloc(sizeof(node)); root->left = root->right = NULL;
    printf("Enter value of root: ");
    scanf("%d", &(root->data));
    for (int i = 0; i<n-1; i++){
        int data;
        printf("Enter data to insert: ");
        scanf("%d", &data);
        insert(&root, data);
        inorder(root);
        printf("\n");
    }

    int num;
    printf("Enter data to delete: ");
    scanf("%d", &num);
    tree deletedNode = delete(&root, num);
    if (deletedNode == NULL){
        printf("Element does not exist in the BST.");
    }
    else{
        printf("Preorder traversal on BST after deleting %d:\n", num);
        preorder(root);
    }
}
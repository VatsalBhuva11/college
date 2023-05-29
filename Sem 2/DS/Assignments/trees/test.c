#include <stdio.h>
#include <stdlib.h>
#include "adt.h"

int main(){
	tree * tree1=NULL;
	printf("\nEnter first value: \n");
	int val;
	scanf("%d",&val);
	insertBinTree(&tree1,val);
	for(int i=0;;i++){
		char c;
		printf("Do you want to enter new value(y or n)?\n");
		scanf(" %c",&c);
		printf("\n");
		if(c=='y'){
			printf("Enter value: \n");
			scanf("%d",&val);
			insertBinTree(&tree1,val);
		}
		else{
			break;
		}
	}
	
	printf("\n\n");
	
	printf("In-order is: \n");
	inorder(tree1);
	printf("\n\n");
	printf("Pre-order is: \n");
	preorder(tree1);
	printf("\n\n");
	printf("Post-order is: \n");
	postorder(tree1);


	//CURRENTLY WORKS ONLY FOR A FULL BINARY TREE
	printf("\n\n_______________________________LCRS______________________________\n\n");
	LCRSconv(tree1);
	// printf("\n%d->%d->%d",tree1->key,tree1->left->key,tree1->left ->left->right->key);
	printf("\n\n");
	printf("Post-order after LCRS rearrangement is: \n");
	traverseLCRS(tree1);
	printf("\n\n");
	return 0;
}
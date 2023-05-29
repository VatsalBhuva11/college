#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

int main(){
    int n;
    scanf("%d", &n);
    struct node *head;
    head = (struct node *)malloc(sizeof(struct node));
    struct node *p = head;
    for (int i = 0; i<n; i++){
        int num;
        scanf("%d", &num);
        p->data = num;
        if (i!=n-1){
            struct node *new = (struct node *)malloc(sizeof(struct node));
            p->next = new;
            p = p->next;
        }
        else{
            p->next = NULL;
        }
    }

    p = head;
    while (p!=NULL){
        printf("%u,%d,%u ", p,p->data,p->next);
        p = p->next;
    }

    return 0;
}

/*
- passing the head pointer from the main function is PASS BY VALUE.
- so, using that head pointer in the required function would be done by a copy of the head pointer.
- changing the values of nodes would done BY REFERENCE since pointers are used to access these nodes.
- causing any change in the position of the head pointer would require it's new position to be returned.
*/
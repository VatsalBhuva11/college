#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

void createPoly(struct node *head, int n){
    struct node *temp = head;
    for (int i = 0; i<n; i++){
        int num;
        scanf("%d", &num);
        temp->data = num;
        if (i==n-1){
            temp->next = NULL;
        }
        else{
            struct node *new = (struct node *)malloc(sizeof(struct node));
            temp->next = new;
            temp = new;
        }
    }
}


void printList(struct node *head, int n){
    struct node *temp = head;
    while (temp->next != NULL){
        printf("%dx^%d + ",temp->data, n-1);
        temp = temp->next;
        n-=1;
    }
    printf("%dx^%d", temp->data, n-1);
    printf("\n");
}

struct node *add(struct node *p1, struct node *p2, int n1, int n2){ //let n1>=n2;
    struct node *res = (struct node *)malloc(sizeof(struct node));
    struct node *temp = res;

    int diff = n1-n2;
    for (int i = 0; i<diff; i++){
        temp->data = p1->data;
        struct node *new = (struct node *)malloc(sizeof(struct node));
        temp->next = new;
        temp = new;
        p1 = p1->next;
    }
    for (int i = 0; i<n2; i++){
        temp->data = p1->data + p2->data;
        if (i==n2-1){
            temp->next = NULL;
        }
        else{
            struct node *new = (struct node *)malloc(sizeof(struct node));
            temp->next = new;
            temp = new;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    return res;
}

int main(){
    printf("Enter degree of first polynomial: ");
    int n1;
    scanf("%d", &n1);
    printf("Enter degree of second polynomial: ");
    int n2;
    scanf("%d", &n2);
    struct node *p1 = (struct node *)malloc(sizeof(struct node));
    struct node *p2 = (struct node *)malloc(sizeof(struct node));
    createPoly(p1,n1);
    createPoly(p2,n2);
    printf("First polynomial: ");
    printList(p1,n1);
    printf("Second polynomial: ");
    printList(p2,n2);

    struct node *ans;
    if (n2>n1){
        ans = add(p2,p1,n2,n1);
    }
    else{
        ans = add(p1,p2,n1,n2);
    }

    int max;
    if (n1>n2) max = n1;
    else max = n2;
    printf("Added polynomial: ");
    printList(ans,max);
}
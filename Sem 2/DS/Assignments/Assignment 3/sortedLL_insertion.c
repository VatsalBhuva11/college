#include <stdio.h>
#include <malloc.h>

struct nd{
    int data;
    struct nd *next;
};
typedef struct nd node;

void printlist(node *head){
    while (head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void insertionSort(node **head, node *element){
    node *moving = (*head)->next, *prev = *head;
    while (moving != NULL){
        if (prev->data > element->data){ //if head->data > element->data, insert before head
            element->next = prev;
            *head = element;
            return;
        }
        if (moving->data >= element->data){ //element inserted in middle of list
            element->next = moving;
            prev->next = element;
            return;
        }
        moving = moving->next;
        prev = prev->next;
    }
    if (moving == NULL){ //either initially (head->next = NULL) or after complete traversal (last->next = NULL)
        if (prev != *head){ //entire list traversed, so inserting element at end.
            prev->next = element;
            element->next = NULL;
        }
        else{ //first insertion when moving is NULL and prev is head
            if ((prev->data) >= (element->data)){ //if element to be inserted before head
                element->next = prev;
                *head = element;
            }
            else{ //if element to be inserted after head
                (*head)->next = element;
                element->next = NULL;
            }
        }
    }
}

int main(){
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    node *head = (node *)malloc(sizeof(node));
    printf("Enter data: ");
    scanf("%d",&(head->data));
    head->next = NULL;
    for (int i = 1; i<n; i++){
        printf("Enter data: ");
        node *p = (node *)malloc(sizeof(node));
        scanf("%d", &(p->data));
        insertionSort(&head, p);
        printlist(head);
    }
    // printf("Sorted List: ");

}



#include <stdio.h>
#include <malloc.h>

struct node{
    int data;
    struct node *next;
};
int n;

void create(struct node **head, int n){
    struct node *temp = *head;
    for (int i = 0; i<n; i++){
        struct node *new = (struct node *)malloc(sizeof(struct node));
        scanf("%d", &new->data);
        new->next = NULL;
        if (*head == NULL) *head = new; //inserting the first element
        //for every iteration, temp points to prev of new.
        else temp->next = new;
        temp = new;
    }
}


void printList(struct node *head){
    while (head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void insert(struct node **head, int element, int pos){
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->data = element;
    if (pos == 0){ //if inserting at head
        new->next = *head;
        *head = new;
    }
    else{
        struct node *temp = *head;
        for (int i = 0; i<pos-1; i++){
            temp = temp->next; //bring temp to prev of insertion position
        }
        new->next = temp->next;
        temp->next = new;
    }
    n++; //update size of linked list
}

void delete_by_elem(struct node **head, int element){
    struct node *temp = *head, *prev;
    if (temp->data == element){ //deletion at head
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp->data != element && temp != NULL){ //find position for deletion
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL){
        printf("Element doesn't exist in list.\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
    n--;
}

void delete_by_pos(struct node **head, int pos){
    struct node *temp = *head, *prev;
    if (pos == 0){
        *head = (*head) -> next;
        free(temp);
    }
    else{
        for (int i = 0; i<pos; i++){
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL){
            printf("Invalid position.\n");
            return;
        }
        prev->next = temp->next;
        free(temp);
    }
}

void swap(struct node *a, struct node *b){
    struct node temp = *a;
    a->data = b->data;
    b->data = temp.data;
}

void selection_sort(struct node *head){
    struct node *temp = head;
    while (temp->next != NULL){
        struct node *min = temp, *after = temp->next;
        while (after != NULL){
            if (after->data < min->data){
                min = after;
            }
            after = after->next;
        }
        swap(temp, min); //swap data of min and temp, keep next of both structures same.
        temp = temp->next;
    }
}

void insertion_sort(struct node **head){
    struct node *temp = *head; int countTempPos = 0;
    while (temp->next != NULL){
        struct node *after = temp->next;
        int i = 0;
        struct node *start = *head;
        while (start != after){
            int num = after->data;
            if (start->data > num){
                delete_by_pos(head, countTempPos+1); //"after" pointer gets freed. so, have to use num and not after->data
                insert(head, num, i);
                break;
            }
            i++;
            start = start->next;
        }
        //temp updated automatically if sorting occurs for a step.
        //if element already in sorted position, temp has to be updated.
        if (start == after) temp = temp->next;
        countTempPos++;
    }
}

void reverse(struct node **head, struct node *curr, struct node *prev){
    if (curr->next == NULL){
        curr->next = prev;
        *head = curr;
    }
    else{
        reverse(head, curr->next, prev->next);
        curr->next= prev;
        prev->next = NULL;
    }
}

int main(){
    printf("Enter number of elements: ");
    scanf("%d", &n);
    struct node *head = NULL;
    create(&head, n);
    printf("Original List is: ");
    printList(head);
    printf("List after inserting 10,50,100: ");
    insert(&head, 50, 1);
    insert(&head, 10, 0);
    insert(&head, 100, n);
    printList(head);
    printf("List after deleting 10,50,100: ");
    delete_by_elem(&head, 10);
    delete_by_elem(&head, 50);
    delete_by_elem(&head, 100);
    printList(head);

    // selection_sort(head);
    // printf("Sorted List (selection sort): ");

    insertion_sort(&head);
    printf("Sorted List (insertion sort): ");
    
    printList(head);

    reverse(&head, head->next, head);
    printf("List after reversal: ");
    printList(head);
}
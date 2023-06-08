#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

int m; //no. of slots

struct node *create(int data){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void insert(int slot, int element, struct node *slots[]){
    struct node *new = create(element);
    if (slots[slot]->next == NULL){
        slots[slot]->next = new; 
    }
    else{
        struct node *temp = slots[slot];
        while (temp->next != NULL) temp = temp->next;
        temp->next = new;
    }
}

void search(int element, struct node *slots[]){
    int slot = element % m;
    struct node *temp = slots[slot]; temp = temp->next;
    if (temp == NULL){
        printf("Came  here.\n");
        printf("Element does not exist.\n");
        return;
    }
    int count = 1;
    while (temp != NULL){
        if (temp->data == element){
            printf("Element found at slot %d, position %d\n", slot, count);
            return;
        }
        temp = temp->next; count++;
    }
}

void delete(int element, struct node *slots[]){
    int slot = element % m;
    struct node *parent = slots[slot];
    struct node *temp = slots[slot]->next;
    if (temp == NULL){
        printf("Element is not present in the hash-table.\n");
        return;
    }
    else{
        int count = 1;
        while (temp != NULL){
            if (temp->data == element){
                printf("Data deleted from slot %d, position %d\n", slot, count);
                parent->next = temp->next;
                free(temp);
                return;
            }
            parent = temp;
            temp = temp->next;
            count++;
        }
        printf("Element is not present in the hash-table.\n");
    }
}

void printHashTable(struct node **slots){
    for (int i = 0; i<m; i++){
        struct node *temp = slots[i]->next;
        printf("%d: ", i);
        if (temp == NULL){
            printf("\n");
            continue;
        }
        while (temp->next != NULL){
            printf("%d --> ", temp->data);
            temp=temp->next;
        }
        printf("%d\n", temp->data);
    }
}

int main(){

    printf("Enter number of keys: ");
    int n;
    scanf("%d", &n);
    
    printf("Enter modulo value: ");
    scanf("%d", &m);
    struct node *slots[m]; //array of m (m<<n) pointers pointing to struct node datatype.
    for (int i = 0; i<m; i++){
        slots[i] = (struct node *)malloc(sizeof(struct node));
        slots[i]->data = i; slots[i]->next = NULL;
        // printf("%d\n", slots[i]->data);
    }
    printf("Enter values to insert:\n");
    for (int i = 0; i<n; i++){
        int data;
        scanf("%d", &data);
        insert(data % m, data, slots);
    }
    printf("The formed hash-table is:\n");
    printHashTable(slots);
    int dataToSearch;
    printf("\nEnter element to search: ");
    scanf("%d", &dataToSearch);
    search(dataToSearch, slots);

    int dataToDelete;
    printf("\nEnter data to delete: ");
    scanf("%d", &dataToDelete);
    delete(dataToDelete, slots);
    printHashTable(slots);
}
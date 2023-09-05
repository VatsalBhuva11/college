#include <bits/stdc++.h>
using namespace std;

struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = NULL;
  }
};*/

Node *removeDuplicates(Node *head)
{
    if (head->next == NULL) return head;
    Node *temp = head->next;
    int start = head->data;
    while (temp != NULL){
        if (temp->data != start){
            start = temp->data;
            
        }
    }
    return head;
}
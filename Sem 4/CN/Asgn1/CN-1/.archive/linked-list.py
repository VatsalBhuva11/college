class Node:
    def __init__(self, data):
        self.data = data
        self.next = None


class LinkedList:

    def __init__(self):
        self.head = None

    def insertAtBeginning(self, new_data):
        new_node = Node(new_data)
        new_node.next = self.head
        self.head = new_node


    def deleteNode(self, position):

        if self.head is None:
            return

        temp = self.head
        if position == 0:
            self.head = temp.next
            temp = None
            return

        for i in range(position - 1):
            temp = temp.next
            if temp is None:
                break
            
        if temp is None:
            return
        
        if temp.next is None:
            return
        
        next = temp.next.next
        temp.next = None
        temp.next = next

    def search(self, key):
        current = self.head
        while current is not None:
            if current.data == key:
                return True
            current = current.next
        return False
    
    def printList(self):
        temp = self.head
        while (temp):
            print(str(temp.data) + " ", end="")
            temp = temp.next


llist = LinkedList()
llist.insertAtBeginning(1)
llist.insertAtBeginning(2)
llist.insertAtBeginning(3)

print('linked list:')
llist.printList()

print("\nAfter deleting an element:")
llist.deleteNode(2)
llist.printList()

print()
item_to_find = 3
if llist.search(item_to_find):
    print(str(item_to_find) + " is found")
else:
    print(str(item_to_find) + " is not found")
/*
Implement these functions in your linked list class:

get(index) : Get the value of the index-th node in the linked list. If the index is invalid, return -1.

addAtHead(val) : Add a node of value val before the first element of the linked list. After the insertion, 
the new node will be the first node of the linked list.

addAtTail(val) : Append a node of value val to the last element of the linked list.

addAtIndex(index, val) : Add a node of value val before the index-th node in the linked list. 
If index equals to the length of linked list, the node will be appended to the end of linked list. 
If index is greater than the length, the node will not be inserted.

deleteAtIndex(index) : Delete the index-th node in the linked list, if the index is valid.

*/

struct Node {
    int val;
    Node *next;
    
    Node() : val(0), next(NULL) {}
    Node(int val) : val(val), next(NULL) {}
};

class MyLinkedList {
private:
    int size = 0;
    Node *head = new Node(0);
    
public:
    /** Initialize your data structure here. */
    MyLinkedList() {}
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
         if (index >= size) {
            return -1;
        }
        Node *curr = head->next;
        while(index) {
            curr = curr->next;
            index--;
        }
        
        return curr->val;
    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
          Node *temp = head->next;
        head->next = new Node(val);
        head->next->next = temp;
        size++;
    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        Node *curr = head;
        
        while(curr->next) {
            curr = curr->next;
        }
        
        Node *temp = curr->next;
        curr->next = new Node(val);
        size++;
        
    }
    
    void addAtIndex(int index, int val) {
        //index == size is ok, as it means 
        // that we are adding to the last node.
       if (index > size) {
            return;
        }
        
        Node *curr = head;
        // we must reach the node which 
        // will be the predecessor.
        while(index) {
            curr = curr->next;
            index--;
        }
        
        Node *temp = curr->next;
        curr->next = new Node(val);
        curr->next->next = temp;
        size++;
    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        // the number of actual nodes
        // in the linked list is always (sz - 1).
        // so here and getindex we should be returning 
        // error.
        if (index >= size) {
            return;
        }
        
        Node *curr = head;
        
        // reach the predecessor
        while(index) {
            curr = curr->next;
            index--;
        }
        // link the predecessor to the next node
        Node *temp = curr->next;
        curr->next = temp->next;
        delete temp;
        size--;
    }
};

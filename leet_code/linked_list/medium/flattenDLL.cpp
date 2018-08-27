/*
You are given a doubly linked list which in addition to the next and previous pointers, 
it could have a child pointer, which may or may not point to a separate doubly linked list. 
These child lists may have one or more children of their own, and so on, to produce a multilevel 
data structure, as shown in the example below.

Flatten the list so that all the nodes appear in a single-level, doubly linked list. You are given the head of the first level of the list.

Example:

Input:
 1---2---3---4---5---6--NULL
         |
         7---8---9---10--NULL
             |
             11--12--NULL

Output:
1-2-3-7-8-11-12-9-10-4-5-6-NULL


*/

class Solution {
public:
   Node* recflat(Node* head){
        Node *node = head;
        Node *temp = NULL;
        Node *prevnode = head; 
        Node *childtail = NULL;
        
        while(node){
            prevnode = node;
            if(node->child){
                temp = node->next;
                childtail = recflat(node->child);
                node->next = node->child;
                node->child->prev = node;
                node->child = NULL;
                childtail->next = temp;
                if(temp) {
                 temp->prev = childtail; 
                 node = temp;
                } else {
                 prevnode = childtail; 
                 node = NULL;
                }
            }else {
             node = node->next;
            }
        }
        return prevnode;
    }
    
    Node* flatten(Node* head) {
        if(head) Node* tail = recflat(head);
        return head;
    }
};


//Another Solution

class Solution {
public:
    Node* flatten(Node* head) {
        //head==null
        if(!head) return head;
        
        //p=head
        Node *p = head;
        
        //go through list by p
          //if p child null, continue
          //else find the end of the child chain, insert child chain
        while(p){
            if(!p->child){
                p = p->next;
                continue;
            }
            Node *temp = p->child;
            while(temp->next)
                temp = temp->next;
            
            temp->next = p->next;
            if(p->next) {
                 p->next->prev = temp;
            }
            
            p->next = p->child;
            p->child->prev = p;
            p->child = NULL;
        }
        return head;
    }
};


//Another solution
class Solution {
public:
    Node* flatten(Node* head) {
        Node *p = head, *nxt;
        
        while(p){
            if(p->child){
                nxt = p -> next;
                p->next = flatten(p->child);
                p->child = NULL;
                p->next->prev = p;
                while(p->next){
                    p = p->next;    
                }
                p->next = nxt;
                if(nxt) {
                 nxt->prev = p;
                }

            } else{
                p = p->next;
            }
        }
        
        return head;
    }
};









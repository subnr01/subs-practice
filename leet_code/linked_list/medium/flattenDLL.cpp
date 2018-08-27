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

// solution
class Solution {
public:
    Node* flatten(Node* head) 
    {
     
        /*
        1. Check for p
        2. if p has a child, the get the next node in the current list.
        3. Call the function recursively and point the return value to p->next
        4. Point the prev of the return value to p and p->child to NULL.
        5. Find the last node in the returned list.
        6. if the next node in the current list is not null, then set the next and prev pointers of the new list and the next              node
        7. return head
        */
        
        Node *p;
        Node *nxt;
        
        p = head;
        
        while (p) 
        {
            if (p->child)
            {
                nxt = p->next;
                p->next = flatten(p->child);
                p->next->prev = p;
                p->child = NULL;
                while(p->next)
                {
                    p = p->next;
                }
                if (nxt) {
                    p->next = nxt;
                    nxt->prev = p; 
                }
            } 
            p = p->next;
        }
        
        return head;
        
    }
};



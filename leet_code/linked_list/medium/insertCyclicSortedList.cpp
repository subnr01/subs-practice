/*
Given a node from a cyclic linked list which is sorted in ascending order, write a function to insert a 
value into the list such that it remains a cyclic sorted list. 
The given node can be a reference to any single node in the list, and may not be necessarily the
smallest value in the cyclic list.

If there are multiple suitable places for insertion, you may choose any place to insert the new value. 
After the insertion, the cyclic list should remain sorted.

If the list is empty (i.e., given node is null), you should create a new single cyclic list and
return the reference to that single node. Otherwise, you should return the original given node.

Example:

1--> 3 --> 4 -->1 and insert 2

Answer:
1->2->3->4-->1
*/

//Solution 1
class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        Node *res = new Node (insertVal, NULL);
        
        if (!head) {
            res->next = res;
            return res;
        }
        
        Node *curr = head;
        Node *nxt = head->next;
        
        while(nxt != head)
        {
            if ((curr->val > nxt->val) &&
                (insertVal >= curr->val || insertVal <= nxt->val)) {
                break;
            }
            
            if (insertVal >= curr->val && insertVal <= nxt->val) {
                break;
            }
            curr = nxt;
            nxt = curr->next;
        }
        
        res->next = curr->next;
        curr->next = res;
        
        return head;
    }
};


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
        auto res = new Node(insertVal, nullptr);
        
        if (head == nullptr) {    
            res->next = res;
            return res;
        }
        
        auto cur = head;
        auto next = head->next;
        
        while(next != head) {
            if (cur->val > next->val &&
                (insertVal >= cur->val || insertVal <= next->val))
                break;
            
            if (insertVal >= cur->val && insertVal <= next->val)
                break;
            
            cur = next;
            next = next->next;
        }
        
        cur->next = res;
        res->next = next;
        
        return head;
    }
};

//Another solution
class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        Node *node = new Node(insertVal, nullptr);
        if (!head) {
            node->next=node;
            return node;
        }
        Node *curr=head;
        // find maximum val
        while (curr->val<=curr->next->val) {
            curr=curr->next;
            if (curr->next==head) break;
        }
        // find insert point
        if (insertVal<curr->val) {
            while (insertVal>curr->next->val) {
                curr=curr->next;
            }
        }
        // insert
        node->next = curr->next;
        curr->next = node;
        return head;
    }
};

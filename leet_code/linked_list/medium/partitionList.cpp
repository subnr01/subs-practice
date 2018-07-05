/*
Given a linked list and a value x, partition it such that all nodes less than
x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5

*/



/*
Another solution
*/
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* dummyLeft = new ListNode(-1);
        ListNode* dummyRight = new ListNode(-1);
        ListNode* leftCur = dummyLeft;
        ListNode* rightCur = dummyRight;
        while(head != nullptr){
            if(head->val < x){
                leftCur->next=head;
                leftCur=leftCur->next;
            }
            else{
                rightCur->next=head;
                rightCur=rightCur->next;
            }
            head=head->next;
        }
        leftCur->next = dummyRight->next;
        rightCur->next = nullptr;             //Very important line
        return dummyLeft->next;
        
    }
};

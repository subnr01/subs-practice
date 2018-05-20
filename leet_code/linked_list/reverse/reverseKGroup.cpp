/*

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

*/


class Solution {
public:


ListNode* reverseKGroup( struct node *head, int k)
{
	if ( !head || !k)
		return;

	int n = k;
	ListNode *current = head;
	ListNode *prev = NULL;
	ListNode *next;

	while (current != NULL && n > 0)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
		n--;
	}

	if ( current != NULL)
	{	
		head->next = reverseKGroup(current,k)
	}

	return prev;
}
};


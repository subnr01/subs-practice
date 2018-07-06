/*
Given a (singly) linked list with head node root, write a function to 
split the linked list into k consecutive linked list "parts".

The length of each part should be as equal as possible: no two parts
should have a size differing by more than 1. This may lead to some parts being null.

Input: 
root = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], k = 3
Output: [[1, 2, 3, 4], [5, 6, 7], [8, 9, 10]]

*/

class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        int len = 0;
        for (ListNode* node = root; node; node = node->next)
            len++;
        int n = len / k, r = len % k;
        vector<ListNode*> ret(k);
        for (int i = 0; i < k && root; ++i) {
            ret[i] = root;
            for (int j = 1; j < n + (i < r); ++j)
                root = root->next;
            ListNode *next = root->next;
            root->next = nullptr;
            root = next;
        }
        return ret;
    }
};

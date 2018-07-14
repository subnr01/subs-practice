/*

Given the following binary tree,
         1
       /  \
      2    3
     / \    \
    4   5    7
After calling your function, the tree should look like:
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL
    
    
*/




class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) {
            return;
        }
        
        TreeLinkNode *first = NULL;
        TreeLinkNode *last = NULL;
        TreeLinkNode *curr = root;
        
        while (curr) {
            
            if (curr->left || curr->right) {
                if (!first) {
                    first = curr->left ? curr->left : curr->right;
                }
                
                if (curr->left && curr->right) {
                    curr->left->next = curr->right;
                }
                
                if (last) {
                    last->next = curr->left ? curr->left : curr->right;
                }
                
                
                last = curr->right? curr->right: curr->left;
            }
            curr = curr->next;
        }
        
        connect(first);
    }
};

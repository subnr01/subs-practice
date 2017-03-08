/*
Given a binary tree

    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer 
should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
For example,
Given the following perfect binary tree,
         1
       /  \
      2    3
     / \  / \
    4  5  6  7
After calling your function, the tree should look like:
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL

*/

class Solution {
public:
    void connect(TreeLinkNode *root) {
        connect_1(root);
    }
    
    void connect_3(TreeLinkNode *node) {
        if (!node || !node->left) return;
        node->left->next = node->right;
        node->right->next = node->next ? node->next->left : NULL;
        connect_3(node->left);
        connect_3(node->right);
    }
    
    void connect_1(TreeLinkNode *root) {
        while (root)
        {
            TreeLinkNode *level = root;
            TreeLinkNode *last = NULL;
            while (level && level->left)
            {
                if (last) last->next = level->left;
                level->left->next = level->right;
                last = level->right;
                level = level->next;
            }
            root = root->left;
        }
    }
    
};

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

/*

delete a node in the BST


Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.
Note: Time complexity should be O(height of tree).
*/



/* 
Solution for a binary tree
*/
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;
        if (root->val == key) {
            if (!root->right) {
                TreeNode* left = root->left;
                delete root;
                return left;
            }
            else {
                TreeNode* right = root->right;
                while (right->left)
                    right = right->left;
                swap(root->val, right->val);    
            }
        }
        root->left = deleteNode(root->left, key);
        root->right = deleteNode(root->right, key);
        return root;
    }
};



/*
Solution for a binary search tree
*/
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;
        
        if (root->val > key) {
            root->left = deleteNode(root->left, key);
        } 
        else if (root->val < key) {
            root->right = deleteNode(root->right, key);
        }
        else if (root->val == key) {
            if (!root->right) {
                TreeNode* left = root->left;
                delete root;
                return left;
            }
            else if (!root->left) {
                TreeNode* right = root->right;
                delete root;
                return right;
            }
            else {
                TreeNode* right = root->right;
                while (right->left)
                    right = right->left;
                
                root->val = right->val;
                root->right = deleteNode(root->right, right->val);      
            }
        }
        
        
        return root;
    }
};

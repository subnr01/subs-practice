/*

delete a node in the BST


Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node
reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.
Note: Time complexity should be O(height of tree).
*/




//iterative, but perfect sln
class Solution {
public:
  TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) return root;
    if (key > root->val) {
      root->right = deleteNode(root->right, key);
    } else if (key < root->val) {
      root->left = deleteNode(root->left, key);
    } else {
      TreeNode* new_root = nullptr;
      if (root->left == nullptr) {
        new_root = root->right;
      } else if (root->right == nullptr) {
        new_root = root->left;
      } else {
        // Find the min node in the right sub tree
        TreeNode* parent = root;
        new_root = root->right;
        while (new_root->left != nullptr) {
          parent = new_root;
          new_root = new_root->left;
        }
        
        if (parent != root) {
          parent->left = new_root->right;
          new_root->right = root->right;
        }
        
        new_root->left = root->left;      
      }
      
      delete root;
      return new_root;
    }
    
    return root;
  }
}; 
      
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

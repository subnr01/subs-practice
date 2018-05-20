/*

Implement an iterator over a binary search tree (BST). 
Your iterator will be initialized with the root node of a BST.
Calling next() will return the next smallest number in the BST.
Note: next() and hasNext() should run in average O(1) time and 
uses O(h) memory, where h is the height of the tree.


*/

class BSTIterator {
    stack<TreeNode *> myStack;
public:
    BSTIterator(TreeNode *root) {
        pushAll(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !myStack.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode *tmpNode = myStack.top();
        myStack.pop();
        pushAll(tmpNode->right);
        return tmpNode->val;
    }

private:
    void pushAll(TreeNode *node) {
        for (; node != NULL; myStack.push(node), node = node->left);
    }
};




class BSTIterator {
private:
    TreeNode *curr = NULL;
    TreeNode *succ = NULL;
    TreeNode *root = NULL;
public:
    BSTIterator(TreeNode *node) {
        root = node;
        
    }
    
    bool hasNext() {
        if (!root) {
            return false;
        }
        
        /* Return the smallest element*/
        if (!curr) {
            curr = root;
            while(curr->left) {
                curr = curr->left;
            }
            succ = curr;
            return true;
        }
        
        if(succ->right) {
            curr = succ->right;
            while(curr->left) {
                curr = curr->left;
            }
            succ = curr;
            return true;
        }
        
        curr = root;
        int x = succ->val;
        succ = NULL;
        
        
        while(curr) {
            if(curr->val > x){
                succ = curr;
                curr = curr->left;
            }
            else if(curr->val < x) {
                curr = curr->right;
            }
            else {
                break;
            }
            
        }
        if(!succ) {
            return false;
        }
        return true;
    }
    
    int next() {
        return succ->val;
    }
    
};

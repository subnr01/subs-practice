/*

Convert a BST to a sorted circular doubly-linked list in-place. 
Think of the left and right pointers as synonymous to the previous and next pointers in a doubly-linked list.
*/



class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        Node *head = NULL, *tail = NULL;
        convert(root, head, tail);
        if (head)
        {
            head->left = tail;
            tail->right = head;
        }
        return head;
    }
    
    void convert(Node* root, Node*& head, Node*& tail)
    {
        if (root == NULL)
            return;
        
        convert(root->left, head, tail);
        root->left = tail;
        
        if (tail != NULL)
            tail->right = root;
        
        if (head == NULL)
            head = root;
        
        tail = root;
        convert(root->right, head, tail);
    }
};

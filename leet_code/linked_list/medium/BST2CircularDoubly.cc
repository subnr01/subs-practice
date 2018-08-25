/*
Convert a BST to a sorted circular doubly-linked list in-place. 
Think of the left and right pointers as synonymous to the previous and next pointers in a doubly-linked list.
*/

//Solution 1 using inorder
class Solution {
public:
    void InOrder(Node* root, Node** head, Node** end) {
        if(root == nullptr) return;
        InOrder(root->left, head, end);
        if(*head == nullptr) {
            *head = root;
            *end = root;
        } else {                
            Node* prev = *end;
            prev->right = root;
            *end = root;
            (*end)->left = prev;
        }
        InOrder(root->right, head, end);
    }
    
    Node* treeToDoublyList(Node* root) {
        Node* head = nullptr;
        Node* end = nullptr;
        InOrder(root, &head, &end);
        if(head != nullptr && end != nullptr) {
            head->left = end;
            end->right = head;
        }
        return head;
    }
};


//Solution2 using merge
class Solution {
private:
    Node* merge(Node* group1, Node* group2) {
        if (group1 == NULL) {
            return group2;
        } else if (group2 == NULL) {
            return group1;
        } else {
            auto group1End = group1->left;
            auto group2End = group2->left;
            group1End->right = group2;
            group2->left = group1End;
            group2End->right = group1;
            group1->left = group2End;
        }
        return group1;
    }
    
public:
    Node* treeToDoublyList(Node* root) {
        if (!root) return NULL;
        
        auto leftHead = treeToDoublyList(root->left);
        auto rightHead = treeToDoublyList(root->right);
        root->right = root;
        root->left = root;
        auto ret = merge(leftHead, root);
        return merge(ret, rightHead);        
    }
};

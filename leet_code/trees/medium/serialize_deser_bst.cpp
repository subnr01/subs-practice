/*

Serialization is the process of converting a data structure or object into a sequence of bits 
so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be 
reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree. There is
no restriction on how your serialization/deserialization algorithm should work. You just need to ensure 
that a binary search tree can be serialized to a string and this string can be deserialized to the original
tree structure.

The encoded string should be as compact as possible.
*/



class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s;
        preorder(root, s);
        return s;
        
    }
    
    void preorder(TreeNode *root, string &s)
    {
        if (!root) {
            return;
        }
        
        s = s + to_string(root->val) + ",";
        preorder(root->left, s);
        preorder(root->right, s);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int n = data.size();
        if (!n) {
            return NULL;
        }
        
        stringstream ss(data);
        string s;
        vector<int> A;
        while(getline(ss, s, ','))
        {
            int c = stoi(s);
            A.push_back(c);
        }
        
        int index = 0;
        return construct (A, index, INT_MIN, INT_MAX);
    }
    
    TreeNode *construct (vector<int> A, int &index, int low, int high)
    {
        if (index == A.size()) {
            return NULL;
        }
        
        int key = A[index];
        if(key<=low || key>=high) {
            return NULL;
        }
        
        index = index + 1;
        TreeNode* root = new TreeNode(key);
        root->left = construct(A,index,low,key);
        root->right = construct(A,index,key,high);
        return root;
    }
};

=============================================================================================



//markker: geeksforgeeks
// This function stores a tree in a file pointed by fp
void serialize(Node *root, FILE *fp)
{
    // If current node is NULL, store marker
    if (root == NULL)
    {
        fprintf(fp, "%d ", MARKER);
        return;
    }
 
    // Else, store current node and recur for its children
    fprintf(fp, "%d ", root->key);
    serialize(root->left, fp);
    serialize(root->right, fp);
}
 
// This function constructs a tree from a file pointed by 'fp'
void deSerialize(Node *&root, FILE *fp)
{
    // Read next item from file. If theere are no more items or next
    // item is marker, then return
    int val;
    if ( !fscanf(fp, "%d ", &val) || val == MARKER)
       return;
 
    // Else create node with this item and recur for children
    root = newNode(val);
    deSerialize(root->left, fp);
    deSerialize(root->right, fp);
}

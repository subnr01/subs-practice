/*
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be 
stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later 
in the same or another computer environment.


Design an algorithm to serialize and deserialize a binary tree

You may serialize the following tree:

    1
   / \
  2   3
     / \
    4   5

as "[1,2,3,null,null,4,5]"


Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
*/

//using stringstream
class Codec
{
    public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root)
    {
        string s = "";
        if(!root)
        {
            s += "null ";
            return s;
        }
        
        s += to_string(root->val) + " ";
        s += serialize(root->left);
        s += serialize(root->right);
        return s;
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data)
    {
        stringstream ss(data);
        string buffer;
        
        vector<string> output;
        while(ss >> buffer)
            output.push_back(buffer);
        
        int index = 0;
        return deserializeHelper(output, index);
    }
    
    TreeNode* deserializeHelper(vector<string> &data, int &index)
    {
        if(data[index] == "null")
            return NULL;
        
        int number = stoi(data[index]);
        TreeNode* root = new TreeNode(number);
        
        root->left = deserializeHelper(data, index += 1);
        root->right = deserializeHelper(data, index += 1);
        
        return root;
    }
};


//Using queues
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root) return "[null]";
        deque<TreeNode *> q;
        string res = to_string(root->val);
        q.push_back(root);
        while(!q.empty())
        {
            TreeNode *curr = q.front();
            q.pop_front();
            res += ",";
            
            if(curr->left == NULL)
                res += "null";
            else
            {
                res += to_string(curr->left->val);
                q.push_back(curr->left);
            }
            
            res += ",";
            if(curr->right == NULL)
                res += "null";
            else
            {
                res += to_string(curr->right->val);
                q.push_back(curr->right);
            }
        }
        
        return res;
        
        
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int i = 0;
        int e = data.find(',',i);
        if(e == -1) return NULL;
                
        TreeNode * root;
        deque<TreeNode *> q;
        
        string val = data.substr(i, e-i);
        if(val == "null") 
        {
            root = NULL;
            return root;
        }
        
        root = new TreeNode(stoi(val));
        q.push_back(root);
        
        
        while(!q.empty())
        {
            TreeNode * curr = q.front();
            q.pop_front();
            
            
            i = e + 1;        
            e = data.find(',',i);
            
            val = data.substr(i, e-i);
            if(val != "null") 
            {
                curr->left = new TreeNode(stoi(val));
                q.push_back(curr->left);
            }
            
            i = e + 1;        
            e = data.find(',',i);
            
            val = data.substr(i, e-i);
            if(val != "null") 
            {
                curr->right = new TreeNode(stoi(val));
                q.push_back(curr->right);
            }
        
        }
        
        return root;
        
    }
};

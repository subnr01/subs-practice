/*
You need to construct a binary tree from a string consisting of parenthesis and integers.

The whole input represents a binary tree. It contains an integer followed by zero, one or
two pairs of parenthesis. The integer represents the root's value and a pair of parenthesis
contains a child binary tree with the same structure.

You always start to construct the left child node of the parent first if it exists.

Example:

Input: "4(2(3)(1))(6(5))"
Output: return the tree root node representing the following tree:

       4
     /   \
    2     6
   / \   / 
  3   1 5   
 

Note:

There will only be '(', ')', '-' and '0' ~ '9' in the input string.

*/


class Solution {
public:
    TreeNode* str2tree(string s) {
        int i = 0;
        //Remember you cannot put 0 here as you are sending a reference.
        return s.size() == 0 ? nullptr : build(s, i);
    }

private:
    TreeNode* build(string& s, int& i) {
        int start = i;
           
        //If it is a negative number
        if (s[i] == '-') {
            i++;
        }
        
        //If it is a two digit number
        while (isdigit(s[i])) {
            i++;
        }
        
        int num = stoi(s.substr(start, i - start));
        TreeNode* node = new TreeNode(num);
        if (s[i] == '(') {
            //Note we are pre-incrementing i;   
            node->left = build(s, ++i);
            // get rid of the closing bracket   
            i++;    
        }
        if (s[i] == '(') {
            //Note we are pre-incrementing i;
            node->right = build(s, ++i);
            // get rid of the closing bracket
            i++;    
        }
        return node;
    }
};

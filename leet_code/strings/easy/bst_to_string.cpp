/*
Input: Binary tree: [1,2,3,4]
       1
     /   \
    2     3
   /    
  4     

Output: "1(2(4))(3)"

Explanation: Originallay it needs to be "1(2(4)())(3()())", 
but you need to omit all the unnecessary empty parenthesis pairs. 
And it will be "1(2(4))(3)".

*/



class Solution {
public:
    string tree2str(TreeNode* t) {
        if (!t) {
            return "";
        }
        
        //Note the else if below
        string val = to_string(t->val);
        if (t->left) {
            val += "(" + tree2str(t->left) + ")";
        } else if (t->right) {
            val += "()";
        }
        
        if (t->right) {
            val += "(" + tree2str(t->right) + ")";
        }
        return val;
    }
    
};

/*

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]

*/

Related topics: String, backtracking

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        
        vector<string> result;
        if (n < 1) {
            return result;
        }
        
        string s;
        func(result, s, n, n); 
        
        return result;
        
    }
    
    
    void func(vector<string> &result, string s, int left, int right)
    {
        if ( left > right) {
                return;
        }
        
        // Mostly left and right are 0
        // for this to happen
        if (left + right == 0) {
            result.push_back(s);
            return;
        }
        
        //do not forget this left > 0 check, 
        // this is how we can enter the right function.
        if (left > 0) {
            s.push_back('(');
            func(result, s, left-1, right);
            s.pop_back();
        }
        
        if (right > 0) {
            s.push_back(')');
            func(result, s, left, right - 1);
            s.pop_back();
        }
        
        return;
    }
};

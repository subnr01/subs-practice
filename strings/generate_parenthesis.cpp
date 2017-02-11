
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



class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        if (n < 1) return result;
        string parens;
        collect(result, parens, n, n);
        return result;
    }
    void collect(vector<string> &result, string &parens, int left, int right) {
        if (left > right || left < 0) return;
        if (left + right == 0) {
            result.push_back(parens);
            return;
        }
        parens.push_back('(');
        collect(result, parens, left - 1, right);
        parens.pop_back();
        parens.push_back(')');
        collect(result, parens, left, right - 1);
        parens.pop_back();
    }
};

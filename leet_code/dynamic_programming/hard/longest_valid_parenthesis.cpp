/*
Given a string containing just the characters '(' and ')', find the length of the 
longest valid (well-formed) parentheses substring.

Example 1:

Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"
Example 2:

Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"


*/


//Related topics: string, dynamic programming

//using stack
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> stk;
        stk.push(-1);
        int maxL=0;
        for(int i=0;i<s.size();i++)
        {
            int t=stk.top();
            if(t!=-1&&s[i]==')'&&s[t]=='(')
            {
                stk.pop();
                maxL=max(maxL,i-stk.top());
            }
            else
                stk.push(i);
        }
        return maxL;
    }
};

//using dnyamic protramming
class Solution {
public:
int longestValidParentheses(string s) {
int len = s.size(), i, res=0, left;
vector<int> dp(len+1,0);

     for(i=1;i<len;++i)
     {
         if(s[i]==')')
         {
             left = i-dp[i]-1;
             if(left>=0 && s[left]=='(') dp[i+1] = dp[i]+2+dp[left];
             res = max(res, dp[i+1]);
         }
     }
     return res;
     
 }
};


//one more soln
class Solution {
public:
int longestValidParentheses(string s) {
        int l = 0, r = 0, res = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') l++;
            else r++;
            if (l == r) res = max(res, 2 * r);
            else if (r > l) l = r = 0;
        }
        l = r = 0;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s[i] == '(') l++;
            else r++;
            if (l == r) res = max(res, 2 * l);
            else if (l > r) l = r = 0;
        }
        return res;
    }
};

/*
Remove the minimum number of invalid parentheses in order to make the input string valid. 
Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).

Example 1:

Input: "()())()"
Output: ["()()()", "(())()"]
Example 2:

Input: "(a)())()"
Output: ["(a)()()", "(a())()"]
Example 3:

Input: ")("
Output: [""]

*/


class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        //清点需要去掉的左括号和右括号的数量
        int mark = 0;
        int left = 0;
        int right = 0;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '('){
                mark++;
            }else if(s[i] == ')'){
                mark--;
            }
            if(mark < 0){
                right++;
                mark++;
            }
        }
        left = mark;
        //回溯找出符合条件的解
        vector<string> res;
        dfs(s, 0, left, right, res);
        return res;   
    }
    
    void dfs(string &s, int start, int left, int right, vector<string> &res){
        if(left == 0 && right == 0){
            if(isValid(s)) res.push_back(s);
        }
        
        for(int i = start; i < s.size(); i++){
            //第一个一定可以删除， 但是从第二个起要避免重复删除一系列相同括号中的一个
            if (i != start && s[i] == s[i - 1]) continue;
            
            if (s[i] == '(' || s[i] == ')') {
                string curr = s;
                curr.erase(i, 1);
                if (right > 0 && s[i] == ')') 
                    dfs(curr, i, left, right - 1, res);
                else if (left > 0 && s[i] == '(')
                    dfs(curr, i, left - 1, right, res);
            }
            
        }
        
    }
    
    bool isValid(string s){
        int mark = 0;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '('){
                mark++;
            }else if(s[i] == ')'){
                mark--;
            }
            if(mark < 0) return false;
        }
        return mark == 0;
    }
};

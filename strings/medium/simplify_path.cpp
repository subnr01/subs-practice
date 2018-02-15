/*

Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"

*/

Points to remember:
1. How stack is used to push and pop items. pop when ".." and push when not ".."
2. How new sytnax is used to traverse elements of a stack.

class Solution {
public:
    string simplifyPath(string path) {
        
        stringstream ss(path);
        string s;
        vector<string> res;
        
        while(getline(ss, s, '/'))
        {
            if (s == "" || s == ".") {
                continue;
            }
            
            else if (s == ".." && !res.empty()) {
                res.pop_back();
            }
            else if (s != "..") {
                res.push_back(s);
            }
            
        }
        
        string ans;
        for (auto str: res) {
            ans += "/" + str;
        }
        
        return ans.empty()? "/": ans;
    }
};

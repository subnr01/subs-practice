/*
Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern
and a non-empty substring in str.

Example 1:

Input: pattern = "abab", str = "redblueredblue"
Output: true
Example 2:

Input: pattern = pattern = "aaaa", str = "asdasdasdasd"
Output: true
Example 3:

Input: pattern = "aabb", str = "xyzabcxzyabc"
Output: false


*/

//91%, see other solns.
class Solution {
public:
bool wordPatternMatch(string pattern, string str) {
    return dfs(pattern,0,str,0);
}    
bool dfs(string &pattern, int pp, string &str, int ps){
    if(pp==pattern.length()&&ps==str.length())
        return true;
    if((pattern.length()-pp>str.length()-ps)||pp==pattern.length())
        return false;
    if(pat2str.find(pattern[pp])==pat2str.end()){
        for(int i=1;ps+i<=str.length();i++){
            string tempstr=str.substr(ps,i);
            if(str2pat.find(tempstr)!=str2pat.end())
                continue;
            pat2str[pattern[pp]]=str.substr(ps,i);
            str2pat[tempstr]=pattern[pp];
            if(dfs(pattern,pp+1,str,ps+i))
                return true;
            str2pat.erase(tempstr);
        }
        pat2str.erase(pattern[pp]);
        return false;
    }
    else{
        string temp=pat2str[pattern[pp]];
        if(temp==str.substr(ps,temp.length()))
            return dfs(pattern,pp+1,str,ps+temp.length());
        else
            return false;
    }
}
private:
unordered_map<char,string> pat2str;
unordered_map<string,char> str2pat;
};

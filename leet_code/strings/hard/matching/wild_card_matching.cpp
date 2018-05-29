/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like ? or *.
Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:

Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
Example 4:

Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
Example 5:

Input:
s = "acdcb"
p = "a*c?b"
Output: false



*/


https://discuss.leetcode.com/topic/21577/my-three-c-solutions-iterative-16ms-dp-180ms-modified-recursion-88ms


//Related topics: DP, backtracking, Greedy

//popular soln
class Solution {
public:
    bool isMatch(string s, string p) {
        int n=s.length(), m=p.length();
        int pid=0, sid=0;
        int pidp=-1, sidp=-1;
        while(sid<n){
            if(p[pid]==s[sid] || p[pid]=='?'){
                pid++; sid++;
            }else if(p[pid]=='*'){
                pidp=pid++; sidp=sid;
            }else{
                if(pidp>-1){
                    pid=pidp+1; sid=++sidp;
                }else{
                    return false;
                }
            }
        }
        while(p[pid]=='*') pid++;
        return pid==m;
    }
};


//DP
class Solution {
public:
    bool isMatch(string s, string p) {
        int pLen = p.size(), sLen = s.size(), i, j, k, cur, prev;
        if(!pLen) return sLen == 0;
        bool matched[2][sLen+1];
        fill_n(&matched[0][0], 2*(sLen+1), false);
        
        matched[0][0] = true;
        for(i=1; i<=pLen; ++i)
        {
            cur = i%2, prev= 1-cur;
            matched[cur][0]= matched[prev][0] && p[i-1]=='*';
            if(p[i-1]=='*') for(j=1; j<=sLen; ++j) matched[cur][j] = matched[cur][j-1] || matched[prev][j];
            else for(j=1; j<=sLen; ++j)            matched[cur][j] =  matched[prev][j-1] && (p[i-1]=='?' || p[i-1]==s[j-1]) ;
        }
            return matched[cur][sLen];
    }
};






//recursive
class Solution {
private:
    bool helper(const string &s, const string &p, int si, int pi, int &recLevel)
    {
        int sSize = s.size(), pSize = p.size(), i, curLevel = recLevel;
        bool first=true;
        while(si<sSize && (p[pi]==s[si] || p[pi]=='?')) {++pi; ++si;} //match as many as possible
        if(pi == pSize) return si == sSize; // if p reaches the end, return
        if(p[pi]=='*')
        { // if a star is met
            while(p[++pi]=='*'); //skip all the following stars
            if(pi>=pSize) return true; // if the rest of p are all star, return true
            for(i=si; i<sSize; ++i)
            {   // then do recursion
                if(p[pi]!= '?' && p[pi]!=s[i]) continue;
                if(first) {++recLevel; first = false;}
                if(helper(s, p, i, pi, recLevel)) return true;
                if(recLevel>curLevel+1) return false; // if the currently processed star is not the last one, return
            }
        }
        return false;
    }
public:
    bool isMatch(string s, string p) {
        int recLevel = 0;
        return helper(s, p, 0, 0, recLevel);
    }
};


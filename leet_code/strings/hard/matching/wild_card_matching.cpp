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

//98%, popular understand this.
class Solution {
public:
    bool isMatch(string s, string p) {
        const int M = s.size();
        const int N = p.size();
        int si = 0, pi = 0;
        int sCurr = -1, pCurr = -1;
        while (si < M) {
            if (pi < N && (s[si] == p[pi] || p[pi] == '?')) {
                ++si;
                ++pi;
            } else if (pi < N && p[pi] == '*') {
                sCurr = si;
                pCurr = ++pi;
            } else if (pCurr != -1) { 
                si = ++sCurr;
                pi = pCurr;
            } else {
                return false;
            }
        }
        while (pi < N && p[pi] == '*') ++pi;

        return pi == N;
    }
};


//DP 2D array
class Solution {
public:
    bool isMatch(string s, string p) {
    int n1 = s.size(), n2 = p.size();
    vector<vector<bool>> res(n1 + 1, vector<bool>(n2 + 1));
    res[0][0] = true;
    /*
    Why is this step needed
    */
    for(int i=1; i<=n2; i++){
        if(p[i-1] == '*')
            res[0][i] = res[0][i-1];
    }
    for(int i=1; i<=n1; i++){
        for(int j=1; j<=n2; j++){
            if(p[j-1] != '*'){
                res[i][j] = (s[i-1] == p[j-1] || p[j-1] == '?') && res[i-1][j-1]; 
            }
            else{
                /* 
                what is the signigicance of this step
                */
                res[i][j] = res[i-1][j] || res[i][j-1];
            }
        }
    }
    return res[n1][n2];
}
};


//DP (Jancou fighter)
class Solution {
public:
    bool isMatch(string s, string p) { 
        int m = s.length(), n = p.length();
        //if (n > 30000) return false; // the trick
        vector<bool> cur(m + 1, false); 
        cur[0] = true;
        for (int j = 1; j <= n; j++) {
            bool pre = cur[0]; // use the value before update
            cur[0] = cur[0] && p[j - 1] == '*'; 
            for (int i = 1; i <= m; i++) {
                bool temp = cur[i]; // record the value before update
                if (p[j - 1] != '*')
                    cur[i] = pre && (s[i - 1] == p[j - 1] || p[j - 1] == '?');
                else cur[i] = cur[i - 1] || cur[i];
                pre = temp;
            }
        }
        return cur[m]; 
    }
};


// this seems faster than DP
//this is not a linear solution, can you prove why
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


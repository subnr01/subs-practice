/*
Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false

*/


//This is tagged
//Dynamic programming, backtracking, greedy






//backtracking/recursive

class Solution {
    // return value:
    // 0: reach the end of s but unmatched
    // 1: unmatched without reaching the end of s
    // 2: matched
    int dfs(string& s, string& p, int si, int pi) {
        if (si == s.size() and pi == p.size()) return 2;
        if (si == s.size() and p[pi] != '*') return 0;
        if (pi == p.size()) return 1;
        if (p[pi] == '*') {
            if (pi+1 < p.size() and p[pi+1] == '*') 
                return dfs(s, p, si, pi+1); // skip duplicate '*'
            for(int i = 0; i <= s.size()-si; ++i) {
                int ret = dfs(s, p, si+i, pi+1);
                if (ret == 0 or ret == 2) return ret; 
            }
        }
        if (p[pi] == '?' or s[si] == p[pi])
            return dfs(s, p, si+1, pi+1);
        return 1;
    }    
    
public:
    bool isMatch(string s, string p) {
        return dfs(s, p, 0, 0) > 1;
    }
};


//Iterative solution (linear time and constant space)
class Solution {
public:
    bool isMatch(string s, string p) {
        int  slen = s.size(), plen = p.size(), i, j, iStar=-1, jStar=-1;

        for(i=0,j=0 ; i<slen; ++i, ++j)
        {
            if(p[j]=='*')
            { //meet a new '*', update traceback i/j info
                iStar = i;
                jStar = j;
                --i;
            }
            else
            { 
                if(p[j]!=s[i] && p[j]!='?')
                {  // mismatch happens
                    if(iStar >=0)
                    { // met a '*' before, then do traceback
                        i = iStar++;
                        j = jStar;
                    }
                    else return false; // otherwise fail
                }
            }
        }
        while(p[j]=='*') ++j;
        return j==plen;
    }
};


//A DP solution is also given here. It has O(N^2) time complexity and O(N) space

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
            if(p[i-1]=='*') for(j=1; j<=sLen; ++j) {
                matched[cur][j] = matched[cur][j-1] || matched[prev][j];
            }
            else 
            { 
                for(j=1; j<=sLen; ++j)   {
                     matched[cur][j] =  matched[prev][j-1] && (p[i-1]=='?' || p[i-1]==s[j-1]) ;
                }
            }    
        }
            return matched[cur][sLen];
    }
};

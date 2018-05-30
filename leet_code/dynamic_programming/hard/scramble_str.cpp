/*
Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.

*/


//Related topics: dp, string

// https://leetcode.com/problems/scramble-string/discuss/29394/My-C++-solutions-(recursion-with-cache-DP-recursion-with-cache-and-pruning)-with-explanation-(4ms)
//recursive soln
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1 == s2)
            return true;
        int l = s1.size();
        if(l == 1)
            return false;
        int s1map = 0, s2map = 0;
        for(int mid = 1;mid < l; ++ mid){
            s1map += 1 << (s1[mid - 1] - 'a');
            s2map += 1 << (s2[mid - 1] - 'a');
            if(s1map != s2map)
                continue;
            if(isScramble(s1.substr(0, mid), s2.substr(0, mid)) && isScramble(s1.substr(mid), s2.substr(mid)))
                return true;
        }
        s1map = 0, s2map = 0;
        
        for(int mid = 1;mid < l; ++ mid){
            s1map += 1 << (s1[mid - 1] - 'a');
            s2map += 1 << (s2[l - mid] - 'a');
            if(s1map != s2map)
                continue;
            if(isScramble(s1.substr(0, mid), s2.substr(l - mid)) && isScramble(s1.substr(mid), s2.substr(0, l - mid)))
                return true;
        }
        return false;
    }
};


class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1 == s2) return true;
        int m = s1.length(), n = s2.length();
        if (m != n) return false;
        
        vector<int> mapping(26, 0);
        for (int i = 0; i < m; i++) {
            mapping[s1[i]-'a']++;
            mapping[s2[i]-'a']--;
        }
        
        for (int i = 0; i < mapping.size(); i++) {
            if (mapping[i] != 0) return false;
        }
        
        for (int i = 1; i < m; i++) {
            if (isScramble(s1.substr(0, i), s2.substr(0, i)) && isScramble(s1.substr(i), s2.substr(i))) return true;
            if (isScramble(s1.substr(0, i), s2.substr(m-i)) && isScramble(s1.substr(i), s2.substr(0, m-i))) return true;
        }
        return false;
    }
};


class Solution {
public:
    bool isScramble(string s1, string s2) {
        int n = s1.size();
        if(n == 0) return 1;
        vector<vector<vector<int>>> table(n+1, vector<vector<int>>(n, vector<int>(n)));
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j)
                table[1][i][j] = (s1[i] == s2[j]);
        }
        for(int len = 2; len <= n; ++len) {
            for(int i = 0; i+len - 1 < n; ++i) {
                for(int j = 0; j + len - 1 < n; ++j) {
                    for(int sz = 1; sz < len; ++sz) {
                        if((table[sz][i][j] && table[len-sz][i+sz][j+sz]) || (table[sz][i][j+len-sz] && table[len-sz][i+sz][j]))
                            table[len][i][j] = 1;
                    }
                }
            }
        }
        return table[n][0][0];
    }
};

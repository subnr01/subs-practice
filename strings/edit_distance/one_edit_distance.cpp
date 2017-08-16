/*

Given two strings S and T, determine if they are both one edit distance apart.

An edit between two strings is one of the following changes.

Add a character
Delete a character
Change a character
Given two string s1 and s2, find if s1 can be converted to s2 with exactly one edit. Expected time complexity is
O(m+n) where m and n are lengths of two strings.

*/


//https://discuss.leetcode.com/topic/17194/4ms-11-lines-c-solution-with-explanations



class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int m = s.length(), n = t.length();
        if (m > n) return isOneEditDistance(t, s);
        if (n - m > 1) return false;
        bool mismatch = false;
        for (int i = 0; i < m; i++) {
            if (s[i] != t[i]) {
                if (m == n) s[i] = t[i];
                else s.insert(i, 1, t[i]);
                mismatch = true; 
                break;
            }
        }
        return (!mismatch && n - m == 1) || (mismatch && s == t);
    }
};

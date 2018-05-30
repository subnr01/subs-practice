/*
Define S = [s,n] as the string S which consists of n connected strings s. For example, ["abc", 3] ="abcabcabc".

On the other hand, we define that string s1 can be obtained from string s2 if we can remove some
characters from s2 such that it becomes s1. For example, “abc” can be obtained from “abdbec” based
on our definition, but it can not be obtained from “acbbe”.

You are given two non-empty strings s1 and s2 (each at most 100 characters long) and two integers 0 ≤ n1 ≤ 106 
and 1 ≤ n2 ≤ 106. Now consider the strings S1 and S2, where S1=[s1,n1] and S2=[s2,n2]. Find the maximum integer M such that [S2,M] can be obtained from S1.

Example:

Input:
s1="acb", n1=4
s2="ab", n2=2

Return:
2


*/


//https://discuss.leetcode.com/topic/72105/c-solution-inspired-by-70664914-with-organized-explanation




//solution using hashmap (fastest 100 %)
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int m1 = s1.size(), m2 = s2.size();
        vector<int> repeated(m2+1,0), visited(m2+1, -1); 
        visited[0] = 0;
        int k = 0, cnt = 0;
        for (int i = 1; i <= n1; i++) {
            for (int j = 0; j < m1; j++) {
                if (s1[j] == s2[k]) {
                    k++;
                    if (k == m2) {
                        k = 0;
                        cnt++;
                    }
                }
            }
            if (visited[k] == -1) {
                repeated[i] = cnt;
                visited[k] = i;
            }
            else {
                int start = visited[k], p = i-start, t = cnt-repeated[start];
                int ans = (n1-start)/p*t + repeated[(n1-start)%p+start];
                return ans/n2;
            }
        }
        return cnt/n2;
    }
};

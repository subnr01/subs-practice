/*

Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will 
not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".


*/

//Related topics: hash table
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        vector<int> smap(256, 0);
        vector<int> pmap(256, 0);
        
        int m = s.length();
        int n = p.length();
        
        if (m < n)
        {
            return res;
        }
        
        for (int i = 0; i < n; i++)
        {
            ++pmap[p[i]];
            ++smap[s[i]];
        }
        
        if (pmap == smap)
        {
            res.push_back(0);
        }
        
        
        for (int i = n; i < m; i++)
        {
            ++smap[s[i]];
            int pre_index = i - n;
            --smap[s[pre_index]];
            if(smap == pmap) {
                res.push_back(pre_index + 1);
            }
        }
        return res;
        
    }
};

/*
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
Return:

[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]


*/



https://discuss.leetcode.com/topic/21038/10-lines-76ms-easy-c-solution-updated-function-signature/2


class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, multiset<string>> mp;
        for (string s : strs) {
            string t = s; 
            sort(t.begin(), t.end());
            mp[t].insert(s);
        }
        vector<vector<string>> anagrams;
        for (auto m : mp) { 
            vector<string> anagram(m.second.begin(), m.second.end());
            anagrams.push_back(anagram);
        }
        return anagrams;
    }
};


Update: as suggested by yswu1234 in the answer, general sort takes O(nlogn) time. In this problem, since the string only contains lower-case alphabets, we can write a sorting function using counting sort (O(n) time) to speed up the sorting process. I write a string sorting function strSort below and using it to sort the string achieves the overall running time 72ms for this problem.


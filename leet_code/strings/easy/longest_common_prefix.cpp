/*
Write a function to find the longest common prefix string amongst an array of strings.

*/

https://leetcode.com/articles/longest-common-prefix/


class Solution {
    public:
        string longestCommonPrefix(vector<string>& strs) {
            string toReturn;
            if (!strs.size()) return toReturn;
            for (int i = 0; i < strs[0].size(); ++i){
                char curr = strs[0][i];
                for (int j = 1; j < strs.size(); ++j){
                    // Do not ignore to check whether i is within length
                    // string at j
                    if (i > strs[j].size()-1 || curr != strs[j][i]) {
                        return toReturn;
                    }
                }
                toReturn.push_back(curr);
            }
            return toReturn;
        }
    };

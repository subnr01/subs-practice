/*
Each replacement operation has 3 parameters: a starting index i, a source word x and a target word y.  
The rule is that if x starts at position i in the original string S, then we will replace that occurrence of x with y.  
If not, we do nothing.

For example, if we have S = "abcd" and we have some replacement operation i = 2, x = "cd", y = "ffff", 
then because "cd" starts at position 2 in the original string S, we will replace it with "ffff"

Example 1:

Input: S = "abcd", indexes = [0,2], sources = ["a","cd"], targets = ["eee","ffff"]
Output: "eeebffff"
Explanation: "a" starts at index 0 in S, so it's replaced by "eee".
"cd" starts at index 2 in S, so it's replaced by "ffff".
Example 2:

Input: S = "abcd", indexes = [0,2], sources = ["ab","ec"], targets = ["eee","ffff"]
Output: "eeecd"
Explanation: "ab" starts at index 0 in S, so it's replaced by "eee". 
"ec" doesn't starts at index 2 in the original S, so we do nothing.




*/

class Solution {
public:
   string findReplaceString(string S, vector<int>& indexes, vector<string>& sources, vector<string>& targets) {
        vector<pair<int, int>> sorted;
       
       for (int i = 0 ; i < indexes.size(); i++) {
            sorted.push_back(make_pair(indexes[i], i));
        }
       
        sort(sorted.rbegin(), sorted.rend());
       
        for (auto ind : sorted) {
            int i = ind.first;
            string s = sources[ind.second];
            string t = targets[ind.second];
            
            if (S.substr(i, s.length()) == s) {
                S = S.substr(0, i) + t + S.substr(i + s.length());
            }
        }
        return S;
    }
};

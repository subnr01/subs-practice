

/*

Given a list of words (without duplicates), please write a program that returns all concatenated words
in the given list of words.
A concatenated word is defined as a string that is comprised entirely of at least two shorter words
in the given array.

Example:
Input: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]

Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]

Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
 "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".

*/


class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        for (const auto &w : words) {
            m[w] = true;
        }
        vector<string> res;
        for (const auto &w : words) {
            if (canForm(w, false)) {
                res.push_back(w);
            }
        }
        return res;
    }
    
    bool canForm(const string &w, bool hasPrefix) {
        // if (w.empty()) return hasPrefix;
        if (hasPrefix && m.count(w) && m[w]) return true;
        int n = w.length();
        string prefix;
        for (int i = 0; i < n - 1; ++i) {
            prefix += w[i];
            if (m.count(prefix) && m[prefix] && canForm(w.substr(i + 1), true)) return m[w] = true;
        }
        return false;
    }
    
    unordered_map<string, bool> m;
};

/*
Given a list of strings words representing an English Dictionary, find the longest word in words
that can be built one character at a time by other words in words. 
If there is more than one possible answer, return the longest word with the smallest lexicographical order.

If there is no answer, return the empty string.
Example 1:
Input: 
words = ["w","wo","wor","worl", "world"]
Output: "world"
Explanation: 
The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".
Example 2:
Input: 
words = ["a", "banana", "app", "appl", "ap", "apply", "apple"]
Output: "apple"
Explanation: 
Both "apply" and "apple" can be built from other words in the dictionary. However, "apple" is lexicographically smaller than "apply".

*/




//Using hashmap
class Solution {
public:
    string longestWord(vector<string>& words) {
        sort(words.begin(), words.end());
        unordered_set<string> built;
        string res;
        for (string w : words) {
            if (w.size() == 1 || built.count(w.substr(0, w.size() - 1))) {
                res = w.size() > res.size() ? w : res;
                built.insert(w);
            }
        }
        return res;
    }
};


//Trie +DFS (look at SOln for complexity)
class Solution {
public:
    string longestWord(vector<string>& words) {
        TrieNode *root = new TrieNode;
        for (const auto& word : words) {
            insert(root, word);
        }
        int mx = 0;
        string str, ans;
        dfs(root, 0, str, mx, ans);
        return ans;
    }
    struct TrieNode {
        TrieNode() {
            memset(ch, 0, sizeof(ch));
            is_end = false;
        }
        TrieNode *ch[26];
        bool is_end;
    };
    void insert(TrieNode *root, const string& word) {
        TrieNode *cur = root;
        for (auto c : word) {
            int j = c - 'a';
            if (!cur->ch[j]) cur->ch[j] = new TrieNode;
            cur = cur->ch[j];
        }
        cur->is_end = true;
    }
    void dfs(TrieNode *root, int depth, string& str, int& mx, string& ans) {
        if (!root) return;
        if (depth > mx) {
            mx = depth;
            ans = str;
        }
        for (int i = 0; i < 26; ++i) {
            if (!root->ch[i] or !root->ch[i]->is_end) continue;
            str.push_back('a' + i);
            dfs(root->ch[i], depth + 1, str, mx, ans);
            str.pop_back();
        }
    }
};

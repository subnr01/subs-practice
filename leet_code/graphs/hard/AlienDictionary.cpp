/*

There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You 
receive a list of words from the dictionary, where words are sorted lexicographically by the rules of this new language. 
Derive the order of letters in this language.
For example, Given the following words in dictionary,
[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]
The correct order is: "wertf".
There are few points not clear :
each word itself has no order, ie abc can not deduce the order of a, b ,c
if any chars has not found and there is no dependence what then ?


*/

//Related topics: topological sort
//https://discuss.leetcode.com/topic/22476/16-18-lines-python-30-lines-c

http://www.geeksforgeeks.org/given-sorted-dictionary-find-precedence-characters/


string alienOrder(vector<string>& words) {
    map<char, set<char>> suc, pre;
    set<char> chars;
    string s;
    for (string t : words) {
        chars.insert(t.begin(), t.end());
        for (int i=0; i<min(s.size(), t.size()); ++i) {
            char a = s[i], b = t[i];
            if (a != b) {
                suc[a].insert(b);
                pre[b].insert(a);
                break;
            }
        }
        s = t;
    }
    set<char> free = chars;
    for (auto p : pre)
        free.erase(p.first);
    string order;
    while (free.size()) {
        char a = *begin(free);
        free.erase(a);
        order += a;
        for (char b : suc[a]) {
            pre[b].erase(a);
            if (pre[b].empty())
                free.insert(b);
        }
    }
    return order.size() == chars.size() ? order : "";
}



//very fast
class Solution {
public:
    string alienOrder(vector<string>& words) {
        vector<unordered_map<char, int>> pre(26, unordered_map<char, int>());
        vector<bool> used(26, false);
        vector<int> value(26, 0);
        int n = words.size(), len = 0;
        for (int i = 0; i < n; i++) {
            for (const auto& iter : words[i]) {
                used[iter - 'a'] = true;
            }
            if (i == 0) { continue; }
            int pos = 0;
            while (pos < words[i - 1].length() && words[i - 1][pos] == words[i][pos]) { pos++; }
            if (pos >= words[i - 1].length()) { continue; }
            pre[words[i - 1][pos] - 'a'][words[i][pos]]++;
            value[words[i][pos] - 'a']++;
        }
        queue<int> wait_queue;
        for (int i = 0; i < 26; i++) {
            len += (used[i] ? 1 : 0);
            if (used[i] && value[i] == 0) {
                wait_queue.push(i);
            }
        }
        string ans;
        while (!wait_queue.empty()) {
            int ch = wait_queue.front();
            wait_queue.pop();
            ans += char(ch + 'a');
            for (const auto& iter : pre[ch]) {
                value[iter.first - 'a'] -= iter.second;
                if (value[iter.first - 'a'] == 0) {
                    wait_queue.push(iter.first - 'a');
                }
            }
        }
        if (ans.length() != len) { return ""; }
        return ans;
    }
};

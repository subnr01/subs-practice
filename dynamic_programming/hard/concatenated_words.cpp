/*

Given a list of words (without duplicates), please write a program that returns all concatenated words
in the given list of words.

A concatenated word is defined as a string that is comprised entirely of at least two shorter words in the given array.

Example:
Input: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]

Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]

Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
 "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
Note:
The number of elements of the given array will not exceed 10,000
The length sum of elements in the given array will not exceed 600,000.
All the input string will only include lower case letters.
The returned elements order does not matter.

*/




//Using hash
vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> result;
        if(words.empty()) return result; 
        auto mycomp = [&](const string& str1, const string& str2){return str1.size() < str2.size();};
        sort(words.begin(), words.end(), mycomp);
        unordered_set<string> mp;
        for(auto& word: words) {
            string path = "";
            if(dfs(word, 0, path, 0, mp)) result.push_back(word); // We don't need to insert this word, because it can be concatenated from other words.
            else mp.insert(word); 
        }
        return result;
    }
    
private:
    bool dfs(string& word, int pos, string& path, int nb, unordered_set<string>& mp) {
        if(pos == word.size()) {
            if(mp.find(path) != mp.end() && nb > 0) return true;
            else return false;
        }
        path.push_back(word[pos]);
        if(mp.find(path) != mp.end()) {
            string temp = "";
            if(dfs(word, pos+1, temp, nb+1, mp)) return true;
        }
        if(dfs(word, pos+1, path, nb, mp)) return true;
        else return false;
    }
    
    
//Using DP
vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> result;
        if(words.empty()) return result; 
        auto mycomp = [&](const string& str1, const string& str2){return str1.size() < str2.size();};
        sort(words.begin(), words.end(), mycomp);
        unordered_set<string> mp;
        for(auto& word: words) {
            string path = "";
            if(wordBreak(word, mp)) result.push_back(word); // We don't need to insert this word, because it can be concatenated from other words.
            else mp.insert(word); 
        }
        return result;
    }
    
private:
    bool wordBreak(string& s, unordered_set<string>& wordDict) {
        if(s.empty() || wordDict.empty()) return false;
        vector<bool> dp(s.size()+1, false);
        dp[0] = true;
        for(int i = 1; i <= s.size(); i++) {
            for(int k = i-1; k >= 0; k--) {
                if(dp[k] && wordDict.find(s.substr(k, i-k)) != wordDict.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.size()];
    }
    



//Using trie
//https://discuss.leetcode.com/topic/72350/c-solutions-backtrack-dp-or-trie/4
struct Node;
using pNode = Node *;
//allocate node on stack instead of heap
pNode pool[27000][26]; // pool size is just tuned by hand to avoid MLE for this question only
struct Node{
    int idx;
    bool end = false;
    Node(int identity):idx(identity){
        memset(pool[idx], 0, sizeof(pool[idx]));  // remember to reset to NULL because the pool might be polluted by the last run
    }    
};
class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        identity = 0; // must reset to 0 because LeetCode judge might use this method as "class static", which is called multi times
        root = new Node(identity++);
        for(auto& w : words)
            if(w.size() < 100) // use a trick here, just skip longer words (specially for this question)
                insert(root, w, 0);
        vector<string> rtn;
        for(auto& w : words){
            f.assign(w.size()+1, 0);  // dp part, f[i] stands for the max number of words in dict that can be combined into w[i:]
            visit.assign(w.size()+1, false); 
            for(int j = (int)w.size()-1; j>=0; j--)
                count(w, j); // calculate reversely to avoid too deep recursion
            if(count(w, 0) > 1)
                rtn.push_back(w);
        }
        collect(root); //must remember to collect history-node, other wise still MLE
        return rtn;
    }
private:
    Node * root;
    int identity = 0;
    vector<int> f;
    vector<bool> visit;
    void collect(Node* ref){
        if(ref){
            for(int i = 0; i < 26; i++)
                collect(pool[ref->idx][i]);
            delete ref;
        }
    }
    void insert(Node* ref, string& s, int i){
        if(i == s.size()){
            ref->end = true;
            return;
        }
        if(pool[ref->idx][s[i]-'a'] == NULL)
            pool[ref->idx][s[i]-'a'] = new Node(identity++);
        ref = pool[ref->idx][s[i]-'a'];   
        insert(ref, s, i+1);    
    }
    int count(string&s, int i){
        if(i == s.size())
            return 0;
        if(visit[i])
            return f[i];
        Node* p = root;
        for(int j = i; j < s.size(); j++){
            if(p && pool[p->idx][s[j]-'a'])
                p = pool[p->idx][s[j]-'a'];
            else
                break;
            if(p->end){
                int l = count(s, j+1);
                f[i] = max(f[i], (l == 0 && j+1 < s.size())? 0 : l+1);
            }
            if((i==0 && f[i] > 1) || (i && f[i])) // early stop to avoid TLE
                break;
        }
        visit[i] = true;
        return f[i];
    }
};

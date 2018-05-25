/*
Implement a MapSum class with insert, and sum methods.

For the method insert, you'll be given a pair of (string, integer). The string represents the key and 
the integer represents the value. If the key already existed, then the original key-value pair will be overridden to the new one.

For the method sum, you'll be given a string representing the prefix, and you need to return the sum of 
all the pairs' value whose key starts with the prefix.

Example 1:
Input: insert("apple", 3), Output: Null
Input: sum("ap"), Output: 3
Input: insert("app", 2), Output: Null
Input: sum("ap"), Output: 5
*/

//Related topics: trie



//trie
class TrieNode {
public:
    TrieNode(bool b = false) {
        value = 0;
        isWord = b;
        memset(next, 0, sizeof(next));
    }   
    ~TrieNode() {
      for (auto& node : next) {
        if (node != nullptr) {
          delete node;
        }   
      }   
    }
    TrieNode* next[26];
    int value;
    bool isWord;
};


class MapSum {
public:
    /** Initialize your data structure here. */
    MapSum() {
        root = new TrieNode;
    }
    
    void insert(string key, int val) {
        TrieNode* node = root;
        for (char& c : key) {
            if (node->next[c-'a'] == nullptr) {
                node->next[c-'a'] = new TrieNode;
            }
            node = node->next[c-'a'];
        }
        node->isWord = true;
        node->value = val;
    }
    
    int sum(string prefix) {
        TrieNode* node = root;
        for (char& c : prefix) {
            if (node->next[c-'a'] == nullptr) {
                return 0;
            }
            node = node->next[c-'a'];
        }
        return dfs(node);
    }
    
    int dfs(TrieNode* node) {
        int sum = 0;
        if (node == nullptr) {
            return sum;
        }
        // similar logic to what I thouhgt, however
        // the important thing here and what I missed is
        // that you have to go through all the 26 nodes
        // because you do not know where the current roots
        // are present along which branch.
        for (int i = 0; i < 26; i++) {
            sum += dfs(node->next[i]);
        }
        return sum += node->value;
    }
private:
    TrieNode* root;
};


//hashmap
class MapSum {
public:
    /** Initialize your data structure here. */    
    void insert(string key, int val) {
        mp[key] = val;
    }
    
    int sum(string prefix) {
        int sum = 0, n = prefix.size();
        for (auto it = mp.lower_bound(prefix); it != mp.end() && it->first.substr(0, n) == prefix; it++) 
            sum += it->second;
        return sum;
    }
private:
    map<string, int> mp;
};


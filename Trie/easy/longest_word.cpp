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
        class Node {
    public:
        bool isWord;
        Node* son[26];
    };
    
    string res="";
    string longestWord(vector<string>& words) {
        Node* root=new Node();
        root->isWord=true;
        for(int i=0;i<words.size();i++) {
            Node* r=root;
            for(int j=0;j<words[i].size();j++) {
                if(r->son[words[i][j]-'a']==NULL) r->son[words[i][j]-'a']=new Node();
                r=r->son[words[i][j]-'a'];
            }
            r->isWord=true;
        }
        DFS(root, "");
        return res;
    }
    
    void DFS(Node* r, string path) {
        if(r==NULL||r->isWord==false) {
            path.pop_back();
            if(path.size()>res.size()) res=path;
            else if(path.size()==res.size()&&res>path) res=path;
            return;
        }
        for(int i=0;i<26;i++) {
            path.append(1, 'a'+i);
            DFS(r->son[i], path);
            path.pop_back();
        }
    }

};

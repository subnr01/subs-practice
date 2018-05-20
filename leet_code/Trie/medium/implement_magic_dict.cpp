/*
Implement a magic directory with buildDict, and search methods.

For the method buildDict, you'll be given a list of non-repetitive words to build a dictionary.

For the method search, you'll be given a word, and judge whether if you modify exactly one character into another character in this word, 
the modified word is in the dictionary you just built.

Example 1:
Input: buildDict(["hello", "leetcode"]), Output: Null
Input: search("hello"), Output: False
Input: search("hhllo"), Output: True
Input: search("hell"), Output: False
Input: search("leetcoded"), Output: False
Note:
You may assume that all the inputs are consist of lowercase letters a-z.
For contest purpose, the test data is rather small by now. You could think about highly efficient algorithm after the contest.
Please remember to RESET your class variables declared in class MagicDictionary, as static/class variables are 
persisted across multiple test cases. Please see here for more details.

*/

//USing hash table
class MagicDictionary {
public:
    /** Initialize your data structure here. */
    MagicDictionary() {
        
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        for (string &s:dict) words.insert(s);
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
          for (int i = 0; i < word.size(); i++) {
            char c = word[i];
            for (int j = 0; j < 26; j++) {
                if (c == j+'a') continue;
                word[i] = j+'a';
                if (words.count(word)) return true;
            }
            word[i] = c;
        }
        return false;
    }
private:
    unordered_set<string> words;
};


//Can you do this with trie????

class MagicDictionary {
public:
    class trieNode {
    public:
        bool flag=false;
        trieNode* sons[26];
    };
    /** Initialize your data structure here. */
    trieNode* root;
    MagicDictionary() {
        root=new trieNode();
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        for(int i=0;i<dict.size();i++) {
            trieNode* r=root;
            for(int j=0;j<dict[i].size();j++) {
                if(r->sons[dict[i][j]-'a']==NULL) r->sons[dict[i][j]-'a']=new trieNode();
                r=r->sons[dict[i][j]-'a'];
                if(j==dict[i].size()-1) r->flag=true;
            }
        }
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
        for(int i=0;i<word.size();i++) {
            char c=word[i];
            for(int j=0;j<26;j++) {
                if(j+'a'==c) continue;
                word[i]=j+'a';
                if(DFS(word)) return true;
                word[i]=c;
            }
        }
        return false;
    }
    
    bool DFS(string w) {
        trieNode* r=root;
        for(int i=0;i<w.size();i++) {
            r=r->sons[w[i]-'a'];
            if(r==NULL) return false;
        }
        return r->flag;
    }
};

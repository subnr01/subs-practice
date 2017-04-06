/*
Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z.

*/

Implementation:

1. Trie datastructure is filled with TrieNodes.
2. Each TrieNode contains 26 Pointers to other TrieNodes.
3. The root of the Trie is a TrieNode and intialised with the constructor.
4. Everytime a word is added, we start from root and we move on to the next letter node pointer.
5. If the next pointer does not exist, then we create the new node.
6. Every trieNode takes a boolean variable which when set means that the trieNode is the end of a word.
7. Find will always start from root and traverse along the Trie to find a last node with boolean set to true.
8. This means that the node exists in the tree.
    
    
    

class TrieNode
{
public:
    TrieNode *next[26];
    bool is_word;
    
    // Initialize your data structure here.
    TrieNode(bool b = false)
    {
        memset(next, 0, sizeof(next));
        is_word = b;
    }
};

class Trie
{
    TrieNode *root;
public:
    Trie()
    {
        root = new TrieNode();
    }
    
    ~Trie(){
        clear(root);
    }

    // Inserts a word into the trie.
    void insert(string s)
    {
        TrieNode *p = root;
        for(int i = 0; i < s.size(); ++ i)
        {
            int ch = s[i] - 'a';
            if(p -> next[ch] == NULL)
                p -> next[ch] = new TrieNode();
            p = p -> next[ch];
        }
        p -> is_word = true;
    }

    // Returns if the word is in the trie.
    bool search(string key)
    {
        TrieNode *p = find(key);
        return p != NULL && p -> is_word;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix)
    {
        return find(prefix) != NULL;
    }

private:
    TrieNode* find(string key)
    {
        TrieNode *p = root;
        for(int i = 0; i < key.size() && p != NULL; ++ i)
        {
            int ch = key[i] - 'a';
            p = p -> next[key[i] - 'a'];
        }
        return p;
    }
    
      void clear(TrieNode *root)
      {
        for(int i = 0; i < 26; i++){
            if(root->next[i] != nullptr){
                clear(root->next[i]);
            }
        }
        delete root;
      }
};

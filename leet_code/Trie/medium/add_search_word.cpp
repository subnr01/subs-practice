/*

Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . 
means it can represent any one letter.

For example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.
*/

Same as the trie implementation, but there is a recursive call
if the tire contains a dot somewhere.

class TrieNode {
public:
    bool m_is_end;
    vector<TrieNode*> children;
    
    TrieNode() {
        m_is_end = false;
        children.resize(26, NULL);
    }
    
    ~TrieNode()
    {
        for (auto child: children)
        {
            delete child;
        }
    }
    
    
};


class WordDictionary {
private:
    TrieNode *root;
public:
    /** Initialize your data structure here. */
    WordDictionary() 
    {
        root = new TrieNode();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) 
    {
        TrieNode *curr = root;
        TrieNode *newNode = NULL;
        for (auto ch : word)
        {
            newNode = curr->children[ch - 'a'];
            if (!newNode) 
            {
                curr->children[ch - 'a'] = new TrieNode();
            }
            curr = curr->children[ch - 'a'];
            
        }
        curr->m_is_end = true;
        
    }
    
    /** 
    Returns if the word is in the data structure. 
    A word could contain the dot character '.' to represent any one letter. 
    */
    bool search(string word) 
    {
        return query(word.c_str(), root);
    }
    
    bool query(const char *word, TrieNode *node)
    {
        TrieNode *curr = node;
        for (int i = 0; word[i] != '\0'; i++)
        {
            char ch = word[i];
            if (curr && ch != '.') {
                curr = curr->children[ch - 'a'];
            } else if (curr && ch == '.')
            {
                for (auto child: curr->children)
                {
                    //THIS LINE IS VERY IMPORTANT
                    curr = child;
                    if (query(word + i + 1, child)) {
                        return true;
                    }
                }
            }
        }
        return curr && curr->m_is_end;
    }
};

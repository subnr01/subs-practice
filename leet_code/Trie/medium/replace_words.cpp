/*
In English, we have a concept called root, which can be followed by some other words to form 
another longer word - let's call this word successor. For example, the root an, followed by other, 
which can form another word another.

Now, given a dictionary consisting of many roots and a sentence. You need to replace all the successor
in the sentence with the root forming it. If a successor has many roots can form it, replace it with the root
with the shortest length.

You need to output the sentence after the replacement.

Example 1:
Input: dict = ["cat", "bat", "rat"]
sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"


*/

/*

Basically the logic is to take all the words in the dictionary and
insert them into the trie and mark the end as root.
The catch however is if we find a subroot inside the word, then we stop
and do not add the full word.

Now when we go into the sentece, we add the space and then take the sentence
and process it through the trie, until we found a root or we found a space.
If there is no root, then leave the root in the as is, if
we found a root, then we replace the word with the root in the sentence.

*/



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

class Trie
{
public:
    TrieNode *root;
    
    Trie()
    {
        root = new TrieNode();
    }
    ~Trie()
    {
        delete root;
    }
    
    void insert(string word)
    {
        insert(word, 0, root);
    }
    
    void insert(string str, int index, TrieNode *curr)
    {
        if (index == str.size()) {
            curr->m_is_end = true;
            return;
        }
        
        if (curr->m_is_end) {
            return;
        }
        
        int ch = str[index] - 'a';
        TrieNode *node = curr->children[ch];
        if (!node)
        {
            curr->children[ch] = new TrieNode();
        }
        curr = curr->children[ch];
        insert(str, index + 1, curr);
    }
    
    int replaceRoot(string sentence, int start)
    {
        int index = 0;
        return numChars(sentence, start, index, root);
    }
    
    int numChars(string sentence, int start, int index, TrieNode *curr)
    {
        /*
         3 conditions:
         1. Reached end of string'
         2. Reached root
         3. Reached space
         */
        
        if (start + index == sentence.size() || curr->m_is_end || sentence[start + index] == ' ')
        {
            return index;
        }
        
        int ch = sentence[start + index] - 'a';
        TrieNode *node = curr->children[ch];
        if (!node)
        {
            
            while(start + index < sentence.size() && sentence[start + index] != ' ')
            {
                index++;
            }
            return index;
        }
        
        curr = curr->children[ch];
        return numChars(sentence, start, index + 1, curr);
        
    }
    
};

class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence)
    {
        Trie t;
        
        for (auto word : dict)
        {
            t.insert(word);
        }
        
        string res;
        int i = 0;
        while(i < sentence.size())
        {
            if (sentence[i] == ' ') {
                res += sentence[i++];
            }
            
            int chars = t.replaceRoot(sentence, i);
            res += sentence.substr(i, chars);
            
            for (i += chars; i < sentence.size() && sentence[i] != ' ';i++);
        }
        //cout<<"hello";
        //cout<<res;
        return res;
    }
};




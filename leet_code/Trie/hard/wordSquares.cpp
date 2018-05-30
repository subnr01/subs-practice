/*
Given a set of words (without duplicates), find all word squares you can build from them.

A sequence of words forms a valid word square if the kth row and column read the exact same string,
where 0 ≤ k < max(numRows, numColumns).

For example, the word sequence ["ball","area","lead","lady"] forms a word square because each word
reads the same both horizontally and vertically.

b a l l
a r e a
l e a d
l a d y

Example 1:

Input:
["area","lead","wall","lady","ball"]

Output:
[
  [ "wall",
    "area",
    "lead",
    "lady"
  ],
  [ "ball",
    "area",
    "lead",
    "lady"
  ]
]

Explanation:
The output consists of two word squares. The order of output does not matter (just the order of
words in each word square matters).
Example 2:

Input:
["abat","baba","atan","atal"]

Output:
[
  [ "baba",
    "abat",
    "baba",
    "atan"
  ],
  [ "baba",
    "abat",
    "baba",
    "atal"
  ]
]

Explanation:
The output consists of two word squares. The order of output does not matter (just the order of words
in each word square matters).

*/


//Trie and backtracking
class Solution {
public:
    struct TrieNode {
        vector<int> indexs;
        vector<TrieNode*> children;
        TrieNode() {
            children.resize(26, nullptr);
        }
    };

    TrieNode* buildTrie(vector<string>& words) {
        TrieNode* root = new TrieNode();
        for (int j = 0; j < words.size(); j++) {
            TrieNode* t = root;
            for (int i = 0; i < words[j].size(); i++) {
                if (!t->children[words[j][i] - 'a'])
                    t->children[words[j][i] - 'a'] = new TrieNode();
                t = t->children[words[j][i] - 'a'];
                t->indexs.push_back(j);
            }
        }
        return root;
    }
    
    vector<vector<string>> res;
    vector<string> vec;
    void backtrack(vector<string>& words, int level, TrieNode* root) {
        if (level >= words[0].size()) {
            res.push_back(vec);
            return;
        }
        string str = "";
        for (int i = 0; i < level; i++) 
            str += vec[i][level];
        TrieNode* t = root;     
        for (int i = 0; i < str.size(); i++) 
            if (!(t = t->children[str[i] - 'a'])) return;
        for (auto index : t->indexs) {
            vec[level] = words[index];
            backtrack(words, level + 1, root);
        }
    }
    
    vector<vector<string>> wordSquares(vector<string>& words) {
        if (words.empty()) return res;
        TrieNode* root = buildTrie(words);
        vec.resize((int)words[0].size());
        for (auto& word : words) {
            vec[0] = word;
            backtrack(words, 1, root);
        }
        return res;
    }
};


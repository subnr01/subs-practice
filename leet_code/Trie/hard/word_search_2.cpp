/*

Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally
or vertically neighboring. The same letter cell may not be used more than once in a word.

For example,
Given words = ["oath","pea","eat","rain"] and board =

[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
Return ["eat","oath"].

*/

class Solution {
private:
class Trie
{
public:    
    Trie * children[26];
    bool isLeaf;
    int  wordIdx;
    int prefixCount;
    
    Trie()
    {
        isLeaf = false;
        wordIdx = 0;
        prefixCount = 0;
        fill_n(children, 26, nullptr);
    }
    
    ~Trie()
    {
        for(auto i=0; i<26; ++i) delete children[i];
    }
};
    void insertWord(Trie *root,  const vector<string>& words, int idx)
    {
        int i, childID, len = words[idx].size();
        for(i=0, root->prefixCount++ ; i<len; ++i)
        {
            childID = words[idx][i]-'a';
            if(!root->children[childID]) root->children[childID] = new Trie();
            root = root->children[childID];
            ++root->prefixCount;
        }
        root->isLeaf = true; 
        root->wordIdx = idx;
    }
    
    Trie *buildTrie(const vector<string> &words)
    {
        Trie *root = new Trie();
        for(int i=0; i < words.size(); ++i) insertWord(root, words, i);
        return root;
    }
    
    int dfs_Trie(vector<string> &res, Trie *root, vector<vector<char>>& board, vector<string>& words, int row, int col)
    {
        int detected = 0;

        if(root->isLeaf)
        {
            ++detected;
            root->isLeaf = false;
            res.push_back(words[root->wordIdx]);
        }
        
        if( row<0 || row>=board.size() || col<0 || col>=board[0].size() || board[row][col]=='*' || !root->children[ board[row][col]-'a'] || root->children[ board[row][col]-'a']->prefixCount <= 0 ) return detected;
        int curC = board[row][col] - 'a';
        board[row][col] = '*';
        detected += dfs_Trie(res, root->children[curC], board, words, row-1, col) + 
               dfs_Trie(res, root->children[curC], board, words, row+1, col) +    
               dfs_Trie(res, root->children[curC], board, words, row, col - 1) +    
               dfs_Trie(res, root->children[curC], board, words, row, col + 1) ;
        root->prefixCount -=detected;
        board[row][col] = curC+'a';
        return detected;
    }
    
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int M, N, wordNum = words.size();
        vector<string> res;
        if( !(M = board.size()) || !(N = board[0].size()) || !wordNum) return res;
        Trie *root = buildTrie(words);
        for(auto i=0; i<M && root->prefixCount; ++i)
            for(auto j=0; j<N; ++j)
                dfs_Trie(res, root, board, words, i, j);
        delete root;
        return res;
    }
};



//compact and slightly faaster
class Solution
{
    public:
    
    struct TrieNode
    {
        TrieNode* next[26];
        string word = "";
    };
    
    vector<string> findWords( vector< vector<char> > &board, vector<string> &words )
    {
        TrieNode* root = buildTrie( words );
        vector<string> result;
        
        for( int i = 0; i < board.size(); i++ )
            for( int j = 0; j < board[i].size(); j++ )
                wordSearch( board, i, j, root, result );
        
        return result;
    }
    
    void wordSearch( vector< vector<char> > &board, int i, int j, TrieNode* root, vector<string> &result )
    {
        char c = board[i][j];
        if( c == ' ' || !root )
            return;
        
        root = root->next[c - 'a'];
        if( root && !root->word.empty() )
        {
            result.push_back( root->word );
            root->word = "";
        }
        else if( !root )
            return;
        
        board[i][j] = ' ';
        
        if( i > 0 ) wordSearch( board, i - 1, j, root, result );
        if( j > 0 ) wordSearch( board, i, j - 1, root, result );
        
        if( i < board.size() - 1 ) wordSearch( board, i + 1, j, root, result );
        if( j < board[i].size() - 1 ) wordSearch( board, i, j + 1, root, result );
        
        board[i][j] = c;
    }
    
    TrieNode* buildTrie( vector<string> words )
    {
        TrieNode* root = new TrieNode();
        
        for( int i = 0; i < words.size(); i++ )
        {
            TrieNode* temp = root;
            
            for( int j = 0; j < words[i].size(); j++ )
            {
                char c = words[i][j] - 'a';
                
                if( !temp->next[c] )
                    temp->next[c] = new TrieNode();
                
                temp = temp->next[c];
            }
            
            temp->word = words[i];
        }
        
        return root;
    }
};

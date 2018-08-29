/*
Given two words (beginWord and endWord), and a dictionary's word list, find all shortest
transformation sequence(s) from beginWord to endWord, such that:

Only one letter can be changed at a time
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
Note:

Return an empty list if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output:
[
  ["hit","hot","dot","dog","cog"],
  ["hit","hot","lot","log","cog"]
]
Example 2:

Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: []

Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.

*/

//Related topics: Array, string, backtracking, Breadfirstsearch, array

//Check other solutions too


//SOln 1 slightly faster  (70%), looks to be more a standard soln
class Solution {
private:
    vector<vector<string>> ans;
public:
    vector<vector<string>> findLadders(string start, string end, vector<string>& words) {
        unordered_set<string> dict;
        for (auto word : words) {
            dict.insert(word);
        }
        //dict.insert(end);
        int len = start.length();
        unordered_map<string, vector<string> > next;
        // mark distance
        unordered_map<string, int> vis;
        queue<string> q;
        vector<string> path;
        ans.clear();
        q.push(start);
        vis[start] = 0;
        while (!q.empty()) {
            string s = q.front(); q.pop();
            if (s == end) break;
            int step = vis[s];
            vector<string> snext;
            // make modification
            for (int i = 0; i < len; i++) {
                string news = s;
                for (char c = 'a'; c <= 'z'; c++) {
                    news[i] = c;
                    // if dict doesn't have this word, skip
                    if (c == s[i] || dict.count(news) == 0) continue;
                    // set distance for new point
                    if (vis.count(news) == 0) {
                        q.push(news);
                        vis[news] = step + 1;
                        //snext.push_back(news);
                    } //else {
                        if (step + 1 == vis[news]) {
                            snext.push_back(news);
                        }
                    //}
                    
                }
            }
            next[s] = snext;
        }
        path.push_back(start);
        dfspath(path, next, vis, start, end);
        return ans;
    }
    void dfspath(vector<string> &path,  unordered_map<string, vector<string> > &next,
                 unordered_map<string, int> &vis, string now, string end){
        if (now == end) ans.push_back(path);
        else {
            auto vec = next[now];
            int visn = vis[now];
            for (int i = 0; i < vec.size(); i++) {
                // search based on distance
                if (vis[vec[i]] != visn + 1) continue;
                path.push_back(vec[i]);
                dfspath(path, next, vis, vec[i], end);
                path.pop_back();
            }
        }
    }
};





//Standard bfs (41%) a bit slow.
vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> ans;
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if(!dict.count(endWord)) return ans;
        vector<string> visited; //record visited words  
        queue<vector<string>> q;  q.push({beginWord});
        while(!q.empty()){
           int n = q.size();
           for(int i = 0 ; i < n; ++i){
               auto cur=q.front(); q.pop();
               auto s = cur.back();
              
               for(auto& c : s){
                   const char origin = c;                  
                   for(c='a'; c<='z'; ++c){  
                       if(!dict.count(s)) continue;
                       auto path = cur; 
                       path.push_back(s); 
                       visited.push_back(s); 
                       if(s==endWord) ans.push_back(path);
                       else q.push(path);
                   }
                
                   c = origin;
               }
               
           }
            
           for(auto& w : visited) dict.erase(w);//erase visited
           visited.clear();
            
        }
        return ans; 
      
    }

---------------------------------------------------------------------------------------------------------------
//Solution 2 (98%) ( too long solution, see when you have time)
class Node;

typedef vector<string> Ladder;
typedef unordered_set<string> StringSet;
typedef bool (*NodeCmper) (Node*, Node*);
typedef set<Node*, NodeCmper> NodeSet;

class Node
{
public:
    string word;
    vector<Node*> parents;

    Node(string w) : word(w) {}
    void addparent(Node* parent) { parents.push_back(parent); }

    // Yield all children of this node, and:
    //   1) If the child is found in $targetlayer, which means we found ladders that
    //      connect BEGIN-WORD and END-WORD, then we get all paths through this node
    //      to its ROOT node, and all paths through the target child node to its ROOT
    //      node, and combine the two group of paths to a group of ladders, and append
    //      these ladders to $ladders.
    //   2) Elif the $ladders is empty:
    //       2.1) If the child is found in $nextlayer, then get that child, and add
    //            this node to its parents.
    //       2.2) Else, add the child to nextlayer, and add this node to its parents.
    //   3) Else, do nothing.
    void yieldchildren(NodeSet& nextlayer, StringSet& wordlist, NodeSet& targetlayer,
                       vector<Ladder>& ladders, bool forward)
    {
        string nextword = word;
        for (int i = 0, n = nextword.length(); i < n; i++) {
            char oldchar = nextword[i];
            for (nextword[i] = 'a'; nextword[i] <= 'z'; nextword[i]++) {
                if (wordlist.count(nextword)) {
                    // now we found a valid child-word, let's yield a child.
                    Node* child = new Node(nextword);
                    yield1(child, nextlayer, targetlayer, ladders, forward);
                }
            }
            nextword[i] = oldchar;
        }
    }

    // yield one child, see comment of function `yieldchildren`
    void yield1(Node* child, NodeSet& nextlayer, NodeSet& targetlayer,
                vector<Ladder>& ladders, bool forward) {
        auto itr = targetlayer.find(child);
        if (itr != targetlayer.end()) {
            for (Ladder path1 : this->getpaths()) {
                for (Ladder path2 : (*itr)->getpaths()) {
                    if (forward) {
                        ladders.push_back(path1);
                        ladders.back().insert(ladders.back().end(), path2.rbegin(), path2.rend());
                    } else {
                        ladders.push_back(path2);
                        ladders.back().insert(ladders.back().end(), path1.rbegin(), path1.rend());
                    }
                }
            }
        } else if (ladders.empty()) {
            auto itr = nextlayer.find(child);
            if (itr != nextlayer.end()) {
                (*itr)->addparent(this);
            } else {
                child->addparent(this);
                nextlayer.insert(child);
            }
        }
    }

    vector<Ladder> getpaths()
    {
        vector<Ladder> ladders;
        if (parents.empty()) {
            ladders.push_back(Ladder(1, word));
        } else {
            for (Node* parent : parents) {
                for (Ladder ladder : parent->getpaths()) {
                    ladders.push_back(ladder);
                    ladders.back().push_back(word);
                }
            }
        }
        return ladders;
    }
};

bool nodecmp(Node* pa, Node* pb)
{
    return pa->word < pb->word;
}

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words;
        for (int i=0;i<wordList.size();i++) words.insert(wordList[i]);
        vector<vector<string>> res;
        if (!words.count(endWord)) return res;
        return findLadders(beginWord, endWord, words);
    }
    
    vector<Ladder> findLadders(string begin, string end, StringSet& wordlist) {
        vector<Ladder> ladders;
        Node headroot(begin), tailroot(end);
        NodeSet frontlayer(nodecmp), backlayer(nodecmp);
        NodeSet *ptr_layerA = &frontlayer, *ptr_layerB = &backlayer;
        bool forward = true;

        if (begin == end) {
            ladders.push_back(Ladder(1, begin));
            return ladders;
        }

        frontlayer.insert(&headroot);
        backlayer.insert(&tailroot);
        // wordlist.insert(end);
        while (!ptr_layerA->empty() && !ptr_layerB->empty() && ladders.empty()) {
            NodeSet nextlayer(nodecmp);
            if (ptr_layerA->size() > ptr_layerB->size()) {
                swap(ptr_layerA, ptr_layerB);
                forward = ! forward;
            }
            for (Node* node : *ptr_layerA) {
                wordlist.erase(node->word);
            }
            for (Node* node : *ptr_layerA) {
                node->yieldchildren(nextlayer, wordlist, *ptr_layerB, ladders, forward);
            }
            swap(*ptr_layerA, nextlayer);
        }

        return ladders;
    }
};

--------------------------------------------------------------------------------------------------------------
  
    

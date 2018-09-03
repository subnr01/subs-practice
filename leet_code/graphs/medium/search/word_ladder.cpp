

/*
Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output: 5

Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.
Example 2:

Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: 0

Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
*/


//Solution
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        
        unordered_set<string> wordDict(wordList.begin(), wordList.end());
        if (wordDict.find(endWord) == wordDict.end()) {
            return 0;
        }
  
        unordered_set<string> head, tail, *phead, *ptail;
        head.insert(beginWord);
        tail.insert(endWord);
        int dist = 2;
        while (!head.empty() && !tail.empty()) {
            if (head.size() < tail.size()) {
                phead = &head;
                ptail = &tail;
            }
            else {
                phead = &tail; 
                ptail = &head;
            }
            unordered_set<string> temp; 
            for (auto itr = phead -> begin(); itr != phead -> end(); itr++) {
                string word = *itr;
                wordDict.erase(word);
                for (int p = 0; p < (int)word.length(); p++) {
                    char letter = word[p];
                    for (int k = 0; k < 26; k++) {
                        word[p] = 'a' + k;
                        if (ptail -> find(word) != ptail -> end())
                            return dist;
                        if (wordDict.find(word) != wordDict.end()) {
                            temp.insert(word);
                            wordDict.erase(word);
                        }
                    }
                    word[p] = letter;
                }
            }
            dist++;
            swap(*phead, temp);
        }
        return 0; 
    }
};

//Another soln
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int n = beginWord.size(), ret = 1;
        unordered_set<string> wordSet(wordList.begin(), wordList.end()), 
                              beginSet{beginWord}, endSet{endWord}, nextSet;
        if(wordSet.erase(endWord) == 0){
            return 0;
        }
        while(!beginSet.empty() && !endSet.empty()){
            ++ret;
            if(beginSet.size() > endSet.size()){
                swap(beginSet, endSet);
            }
            for(string word: beginSet){
                for(int i = 0; i < n; ++i){
                    for(char j = 'a'; j <= 'z'; ++j){
                        char ch = word[i];
                        word[i] = j;
                        if(endSet.count(word) != 0){
                            return ret;
                        }
                        if(wordSet.count(word) != 0){
                            wordSet.erase(word);
                            nextSet.insert(word);
                        }
                        word[i] = ch;
                    }
                }
            }
            beginSet = nextSet;
            nextSet.clear();   
        }
        return 0;     
    }
};

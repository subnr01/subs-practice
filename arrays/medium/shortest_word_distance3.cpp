/*

This is a follow up of Shortest Word Distance. The only difference is now word1 could be the same as word2.

Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

word1 and word2 may be the same and they represent two individual words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “makes”, word2 = “coding”, return 1.
Given word1 = "makes", word2 = "makes", return 3.

Note:
You may assume word1 and word2 are both in the list.

*/


int shortestWordDistance(vector<string>& words, string word1, string word2) {
    int res = words.size(), 
    int l = words.size(), 
    int r = -words.size();
    for (unsigned int i=0; i<words.size(); i++) {
        if (words[i] == word1) {
            l = (word1==word2)?r:i;
        }
        if (words[i] == word2) {
            r = i;
        }
        res = min(res, abs(l-r));
    }
    return res;
}


/*
Using hashmap
THIS SOLN MAKES MORE SENSE FOR THE QUESTION
*/

class Solution {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        unordered_map<string,vector<int>> indexOf;
        int N=(int)words.size();
        int mini=N;
        
        for (int i=0; i<N; ++i) {
            indexOf[words[i]].push_back(i);
        }
        for (auto i: indexOf[word1]) 
        {
            for (auto j: indexOf[word2])
            {
                if (i!=j) {
                    mini=min(mini,abs(i-j));
                }
            }
        }
    
        return mini<N ? mini : 0;
    }
};

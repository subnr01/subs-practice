/*
Given a paragraph and a list of banned words, return the most frequent word that is not in the list of banned words.  
It is guaranteed there is at least one word that isn't banned, and that the answer is unique.

Words in the list of banned words are given in lowercase, and free of punctuation.  
*/


class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        unordered_map<string, int>m;
        //Notice "i" is not incremented here
        for(int i = 0; i < paragraph.size();){
            string s;
            while(i < paragraph.size() && isalpha(paragraph[i])) {
                s.push_back(tolower(paragraph[i++]));
            }
            while(i < paragraph.size() && !isalpha(paragraph[i])) {
                i++;
            }
            m[s]++;
        }
        for(auto x: banned) m[x] = 0;
        string res = "";
        int count = 0;
        for(auto x: m)
            if(x.second > count) {
                res = x.first, count = x.second;
            }
        return res;  
    }
};

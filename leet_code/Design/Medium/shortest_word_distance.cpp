/*
Design a class which receives a list of words in the constructor, and implements a
method that takes two words word1 and word2 and return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1.




*/


class WordDistance {
public:
    WordDistance(vector<string> words) {
        for (int i = 0; i < words.size(); i++)
        {
            map[words[i]] .push_back(i);
        }
    }
    
    int shortest(string word1, string word2) {
        int i = 0;
        int j = 0;
        int min_dist = INT_MAX;
        
        while(i < map[word1].size() && j < map[word2].size())
        {
            // do not forget abs
            int dist = abs(map[word1][i] - map[word2][j]);
            min_dist = min(dist, min_dist);
            
            //see how i and j are manipulated without using two
            // for loops. we compare the indices in the value vectors.
            if (map[word1][i] < map[word2][j])
            {
                i++;
            } else {
                j++;
            }
        }
        
        return min_dist;
        
    }
    unordered_map<string, vector<int>> map;
};


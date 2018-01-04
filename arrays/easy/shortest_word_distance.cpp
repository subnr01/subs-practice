/*

Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1.


*/

//https://www.programcreek.com/2014/08/leetcode-shortest-word-distance-java/


int shortestDistance(vector<string>& words, string word1, string word2) {
    int id1 = -1, id2 = -1;
    int minDist = INT_MAX;
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == word1) {
            id1 = i;
            if (id2 != -1) {
                minDist = min(minDist, id1 - id2);
            }
        } else if (words[i] == word2) {
            id2 = i;
            if (id1 != -1) {
                minDist = min(minDist, id2 - id1);
            }
        }
    }
    return minDist;
}

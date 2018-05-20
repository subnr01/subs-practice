/*
Write a function to generate the generalized abbreviations of a word.

Example:
Given word = "word", return the following list (order does not matter):

["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]

*/

//This question is also in bit manipulation. Check out bit manipulation for
// that version of the answer.


//input = word
//output = ["word","wor1","wo1d","wo2","w1rd","w1r1","w2d","w3","1ord","1or1","1o1d","1o2","2rd","2r1","3d","4"]



class Solution {
public:
    vector<string> generateAbbreviations(string word) {
        vector<string> result;
        Helper(word, "", 0, result, false);
        return result;
    }
    
    void Helper(string& word, string abbr, int i, vector<string>& result, bool prevNum) {
        if (i == word.length()) {
            result.push_back(abbr);
            return;
        }
        
        Helper(word, abbr+word[i], i+1, result, false);
        //if previously number has not been added
        if (!prevNum) {
            // Add number abbreviations only when we added a character 
            // instead of an abbreviation earlier
            for (int len = 1; i+len <= word.length(); ++len) {
                // check the (i+len) being passed rather 
                // than (i+1)
                Helper(word, abbr+to_string(len), i+len, result, true);
            }
        }
    }
};

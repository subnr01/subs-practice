/*
Given a word, you need to judge whether the usage of capitals in it is right or not.

We define the usage of capitals in a word to be right when one of the following cases holds:

All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital if it has more than one letter, like "Google".
Otherwise, we define that this word doesn't use capitals in a right way.

Example 1:
Input: "USA"
Output: True
Example 2:
Input: "FlaG"
Output: False

*/


class Solution {
public:
   bool detectCapitalUse(string word) {
    int count = 0;
    if(word.size() <= 1) {
        return true;
    }
    
    //i is intialised from 1
    for( int i = 1; i < word.size(); i++) {
        if(word[i] >= 'a' && word[i] <= 'z') {
            count+=1;
        } else {
            // note count is increased by 2
            count+=2;
        }
    }
    if(count == word.size()-1) {
        return true;
    }
    // we are checking again with (n-1)
    else if(count == 2*(word.size()-1)) {
        return (word[0] >= 'A' && word[0] <= 'Z');
    }
    
    return false;
}
};

/*
Given a string, you need to reverse the order of characters in 
each word within a sentence while still preserving whitespace and initial word order

Example:
Input: "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"

In the string, each word is separated by single space and there will not be any extra space in the string.
*/



//This logic works because on mainly the words 
// are seperated by a single space.
class Solution {
public:
    string reverseWords(string s) {
        size_t front = 0;
        for(int i = 0; i <= s.length(); ++i){
            //we need to check for s.length() as 
            // if we do not do that, then we cannot 
            // reverse the last word
            if(i == s.length() || s[i] == ' '){
                reverse(&s[front], &s[i]);
                // to move beyond the space
                front = i + 1;
            }
        }
        
        return s;
    }
};

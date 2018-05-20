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
        
        int front = 0;
        
        for (int i = 0; i <= s.size(); i++)
        {
            //Notice we are comparing i to length,
            // as we want the last word too.
            if (i == s.size() || s[i] == ' ')
            {
                reverse(s.begin() + front, s.begin() + i);
                front = i + 1;
            }
            
        }
        
        return s;
        
    }
};

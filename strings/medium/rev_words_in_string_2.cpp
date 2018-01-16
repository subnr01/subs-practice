/*
Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.

The input string does not contain leading or trailing spaces and the words are always separated by a single space.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Could you do it in-place without allocating extra space?

*/


/*

The idea is simple: reverse the full string s first and then reverse each word in it in place. 
For reversing each word, we just need to locate the left and right boundaries of the word. The code is as follows.

*/

class Solution { 
public:
    void reverseWords(string &s) {
        reverse(s.begin(), s.end());
        int n = s.length(), l = 0, r = 0;
        while (r < n) {
            while (r < n && !isspace(s[r])) r++;
            reverse(s.begin() + l, s.begin() + r); 
            l = ++r;
        }
    } 
};

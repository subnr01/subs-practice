/*
Given an input string , reverse the string word by word. 

Example:

Input:  ["t","h","e"," ","s","k","y"," ","i","s"," ","b","l","u","e"]
Output: ["b","l","u","e"," ","i","s"," ","s","k","y"," ","t","h","e"]
Note: 

A word is defined as a sequence of non-space characters.
The input string does not contain leading or trailing spaces.
The words are always separated by a single space.

*/

class Solution {
public:
    void reverseWords(vector<char>& str) {
        for(int i = 0; i < str.size(); i++){
            int j = i + 1;
            while(j < str.size() && str[j] != ' ') j++;
            int a = i, b = j - 1;
            while(a < b) swap(str[a++], str[b--]);
            i = j;
        }
        reverse(str.begin(), str.end());
    }
};

/*
Reverse a string
*/


Points to remember:
-- Loops runs from 0 till n/2.
-- swap i and (n-1)-i meaning first and last.

class Solution {
public:
    string reverseString(string s) {
        int n = s.size();
        for(int i = 0; i < n/2; i++) {
            swap(s[i], s[(n - 1) - i]);
        }
        return s;
    }
};

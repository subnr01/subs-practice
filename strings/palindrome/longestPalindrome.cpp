/*

Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that 
can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7

Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
FInd the length of the longest palindrome


*/

int longestPalindrome(string s) {
        vector<int> v(256,0);
        for(int i = 0; i < s.size(); ++i)
           ++v[s[i]];
        int res = 0;
        bool odd = false;
        for(int i = 0; i < 256; ++i)
           if(v[i]%2 == 0)
               res += v[i];
            else
            {
               res += v[i] - 1;
               odd = true;
            }
        if(odd)
          ++res;
        return res;
    }

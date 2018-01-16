/*
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
Example:
Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example:
Input: "cbbd"
Output: "bb"
*/

//http://articles.leetcode.com/longest-palindromic-substring-part-i/

string longestPalindrome(string s) {
    if (s.empty()) {
        return "";
    }
    if (s.size() == 1) {
        return s;
    }
    int min_start = 0;
    int max_pal_len = 1;
    //initialise i to 0, important
    int i = 0;
    while(i < s.size()) 
    {
      //obtained length is greater than what is left in the string.
      if (s.size() - i <= max_pal_len / 2) {
          break;
      }
      
      int j = i; 
      int k = i;
      while (k < s.size()-1 && s[k+1] == s[k]) {
          ++k; // Skip duplicate characters.
      }
      
      i = k+1;
      //since checking with less than (n-1), k + 1 is ok.
      while (k < s.size()-1 && j > 0 && s[k + 1] == s[j - 1]) { 
          ++k; 
          --j; 
      } // Expand.
      
      int new_len = k - j + 1;
      if (new_len > max_pal_len) {
          //remember start is updated only if j is updated
          min_start = j; 
          max_pal_len = new_len; 
      }
    }
    return s.substr(min_start, max_pal_len);
}

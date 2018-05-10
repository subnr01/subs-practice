/*
Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, 
"pwke" is a subsequence and not a substring.

*/

/*
Trace
abba and pwwkew as good examples
*/


class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int maxcount = 0;
        int i = 0;
        int j = 0;
        set<char> myset;
        
        while (j < s.size())
        {
            if (myset.find(s[j]) == myset.end())
            {
                myset.insert(s[j++]);
                maxcount = max(maxcount, (int)myset.size());
            } else {
                myset.erase(s[i++]);
            }
        }
        return maxcount;
        
    }
};

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        
        if (s.size() <= 1) {
            return s.size();
        }
        unordered_map<char, int> m;
        int start = -1;
        int maxlen = 0;
        int i;
        for (i = 0; i < s.size(); i++)
        {
            //Look how the count function is useful    
            if (m.count(s[i]) != 0) {
                //why we need to take "max". "abba" is a fine example
                start = max(start, m[s[i]]);
                
            }
            m[s[i]] = i;
            maxlen = max(maxlen, i - start);
        }
        
        return maxlen;
    }
};



//Another interesting solution
int lengthOfLongestSubstring(string s) {
  int n = s.length();
  int i = 0, j = 0;
  int maxLen = 0;
  bool exist[256] = { false };
  while (j < n) {
    if (exist[s[j]]) {
      maxLen = max(maxLen, j-i);
      while (s[i] != s[j]) {
        exist[s[i]] = false;
        i++;
      }
      i++;
      j++;
    } else {
      exist[s[j]] = true;
      j++;
    }
  }
  maxLen = max(maxLen, n-i);
  return maxLen;
}

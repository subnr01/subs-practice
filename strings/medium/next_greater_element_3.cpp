/*
Given a positive 32-bit integer n, you need to find the smallest 32-bit integer which
has exactly the same digits existing in the integer n and is greater in value than n. 
If no such positive 32-bit integer exists, you need to return -1.

Example 1:
Input: 12
Output: 21
Example 2:
Input: 21
Output: -1


*/

Related topics: string


class Solution {
public:
    int nextGreaterElement(int n) {
        //s = 59876
        string s = to_string(n);
        int len = s.size();
        if (len <= 1) {
            return -1;
        }
        
        int i;
        
        
        for (i = len - 2; i >= 0 ; i--) { 
          //find the prev less integer (5)9876 
          if (s[i] < s[i+1]) {
                break;
            }
        }
        
        if (i == -1) { 
            return -1;
        }
        
        //reverse: 56789
        reverse(s.begin() + i + 1, s.end());
        
        
        for (int j = i + 1; j < len; j++) {
            // 56789 --> 65789 (> 59876)
            if (s[j] > s[i]) {
                swap(s[i], s[j]);
                break;
            }
        }
        long next = stol(s);
        //this is important, as if number is greater than 32 bit,
        // we need to return -1.
        return next == n || next > INT_MAX ? -1 : next;
    }
};

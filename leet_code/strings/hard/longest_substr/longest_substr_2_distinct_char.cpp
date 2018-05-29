/*

Given a string s , find the length of the longest substring t  that contains at most 2 distinct characters.

Example 1:

Input: "eceba"
Output: 3
Explanation: t is "ece" which its length is 3.
Example 2:

Input: "ccaabbb"
Output: 5
Explanation: t is "aabbb" which its length is 5.

*/

//Related topics: hash table, 2 pointers, string
int lengthOfLongestSubstringTwoDistinct(string s) {
    if(s.empty()) return 0;
    
    int dict[256]; 
    fill_n(dict,256,0);
    int start = 0, len = 1, count = 0;
    for(int i=0; i<s.length(); i++) {
        dict[s[i]]++;
        if(dict[s[i]] == 1) { // new char
            count++;
            while(count > 2) {
                dict[s[start]]--;
                if(dict[s[start]] == 0) count--; 
                start++;
            }
        }
        if(i-start+1 > len) len = i-start+1;
    }
    return len;
}


//Another soln ( 100%)

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int ret = 0, p = 1, sz = s.size();
        if (sz < 2) return sz;
        while (p < sz && s[p] == s[p-1]) p++;
        if (p == sz) return sz;
        
        char dch = s[p-1];
        int cnt = 1, dcnt = ++p;
        ret = max(ret, dcnt);
        while (p < sz) {
            if (s[p] == s[p-1]) {
                cnt++; dcnt++;
                ret = max(ret, dcnt);
            } else if (s[p] == dch) {
                cnt = 1; dcnt++;
                dch = s[p-1];
                ret = max(ret, dcnt);
            } else {
                dcnt = cnt + 1;
                dch = s[p-1];
                cnt = 1;
            }
            p++;
        }
        return ret;
    }
};
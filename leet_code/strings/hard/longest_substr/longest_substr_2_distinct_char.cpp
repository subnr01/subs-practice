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
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        std::vector<int> freq(256, 0);
        int k = 2;
        int res = 0, cnt = 0;
        for(int i = 0, j = 0; j < s.size(); j++){
            if(freq[s[j]]++ == 0) cnt++;
            while(cnt > k){
                if(--freq[s[i++]] == 0) cnt--;
            }
            res = max(res, j-i+1);
        }
        return res;
    }
};


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

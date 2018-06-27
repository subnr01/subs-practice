/*

Given a string, find the length of the longest substring T that contains at most k distinct characters.

For example, Given s = “eceba” and k = 2,

T is "ece" which its length is 3.

*/

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        std::vector<int> freq(256, 0);
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


//Solution using map
class Solution {
public:
   int lengthOfLongestSubstringKDistinct(string s, int k) {
    unordered_map<char, int> ctr;
    int j = -1, maxlen = 0;
    for (int i=0; i<s.size(); ++i) {
        ++ctr[s[i]];
        while (ctr.size() > k)
            if (--ctr[s[++j]] == 0)
                ctr.erase(s[j]);
        maxlen = max(maxlen, i - j);
    }
    return maxlen;
}
};


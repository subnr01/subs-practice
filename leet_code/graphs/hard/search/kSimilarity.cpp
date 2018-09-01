/*

Strings A and B are K-similar (for some non-negative integer K) if we can swap the 
positions of two letters in A exactly K times so that the resulting string equals B.

Given two anagrams A and B, return the smallest K for which A and B are K-similar.

Example 1:

Input: A = "ab", B = "ba"
Output: 1
Example 2:

Input: A = "abc", B = "bca"
Output: 2
Example 3:

Input: A = "abac", B = "baca"
Output: 2
Example 4:

Input: A = "aabc", B = "abca"
Output: 2

*/

//BFS Soln
class Solution {
public:
    int kSimilarity(string A, string B) {
        if(A == B) return 0;
        queue<string> mq;
        unordered_set<string> dirs;
        mq.push(A);
        dirs.insert(A);
        int res = 0;
        while(!mq.empty()) {
            res++;
            for(int k = mq.size(); k > 0; k--) {
                string cur = mq.front();
                mq.pop();
                int i = 0;
                while(cur[i] == B[i]) i++;
                for(int j = i+1; j < cur.size(); j++) {
                    if(cur[j] == B[j] || cur[i] != B[j]) continue;
                    swap(cur[i], cur[j]);
                    if(cur == B) return res;
                    if(dirs.find(cur) == dirs.end()) {
                        dirs.insert(cur);
                        mq.push(cur);
                        //break;
                    }
                    swap(cur[i], cur[j]);
                }
            }
        }
        return res;
    }
};


//DP Soln
class Solution {
public:
    unordered_map<string, int> map;
    
    int dp(string& s, string& t, int i) {
        if (i==s.size()) return 0;
        if (map.count(t.substr(i))) 
            return map[t.substr(i)];
        
        int& ans = map[t.substr(i)];
        
        ans = INT_MAX;
        if (s[i]==t[i])
            ans = dp(s, t, i+1);
        else {
            vector<int> one, two;
            for (int j=i+1; j<t.size(); ++j)
                if (t[j]==s[i] && t[i]==s[j])
                    two.push_back(j);
                else if (t[j]==s[i])
                    one.push_back(j);
            if (two.size()) two.resize(1);
            vector<int>& pos = two.size() ? two : one;
            for (auto j: pos) {
                swap(t[i], t[j]);
                ans = min(ans, dp(s, t, i+1)+1);
                swap(t[i], t[j]);
            }
        }
        return ans;
    }
    
    int kSimilarity(string s, string t) {
            
        return dp(s, t, 0);
        
    }
};

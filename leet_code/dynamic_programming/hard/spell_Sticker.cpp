/*

We are given N different types of stickers. Each sticker has a lowercase English word on it.

You would like to spell out the given target string by cutting individual letters from your collection of stickers and rearranging them.

You can use each sticker more than once if you want, and you have infinite quantities of each sticker.

What is the minimum number of stickers that you need to spell out the target? If the task is impossible, return -1.

Example 1:

Input:

["with", "example", "science"], "thehat"
Output:

3
Explanation:

We can use 2 "with" stickers, and 1 "example" sticker.
After cutting and rearrange the letters of those stickers, we can form the target "thehat".
Also, this is the minimum number of stickers necessary to form the target string.
Example 2:

Input:

["notice", "possible"], "basicbasic"
Output:

-1
Explanation:

We can't form the target "basicbasic" from cutting letters from the given stickers.
Note:

stickers has length in the range [1, 50].
stickers consists of lowercase English words (without apostrophes).
target has length in the range [1, 15], and consists of lowercase English letters.
In all test cases, all words were chosen randomly from the 1000 most common US English words, and
the target was chosen as a concatenation of two random words.
The time limit may be more challenging than usual. It is expected that a 50 sticker test case can be 
solved within 35ms on average.


*/


//Look at discussion tab
//contest winner, nut slow
class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
    int n = target.size(), N = 1 << n;
    vector<uint> dp(N, -1);
    dp[0] = 0;
    for (int i = 0; i < N; i++) if (dp[i] != -1) {
        for (string& s : stickers) {
            int now = i;
            for (char c : s) {
                for (int r = 0; r < n; r++) {
                    if (target[r] == c && !((now >> r) & 1)) {
                        now |= 1 << r;
                        break;
                    }
                }
            }
            dp[now] = min(dp[now], dp[i] + 1);
        }
    }
    return dp[N-1];
}
};


//100%
class Solution {
    
public:
    int minStickers(vector<string>& stickers, string target) {
        vector<vector<int>> dict(stickers.size(), vector<int>(26, 0));
        for (int i = 0; i < stickers.size(); ++i) {
            for (char c: stickers[i]) {
                ++dict[i][c-'a'];
            }
        }        
        
        unordered_set<string> visited;
        queue<string> q;
        q.push(target);
        visited.insert(target);
        
        int qSize = q.size();
        int len = 1;
        while (!q.empty()) {
            string s = q.front();
            q.pop();
            --qSize;
            
            vector<int> targetCount(26, 0);
            for (char c: s) {
                ++targetCount[c-'a'];
            }
            
            for (int i = 0; i < stickers.size(); ++i) {
                if(!dict[i][s[0]-'a']) continue;
                vector<int> count(targetCount.begin(), targetCount.end());
                string newStr;
                for (int j = 0; j < 26; ++j) {
                    count[j] -= dict[i][j];
                    if (count[j] > 0) {
                        newStr.append(count[j], 'a'+j);
                    }
                }
                if (newStr.size() == 0) return len;
                else if (!visited.count(newStr)) {
                    q.push(newStr);
                    visited.insert(newStr);
                }
            }
            
            if (qSize == 0) {
                qSize = q.size();
                ++len;
            }
        }
        return -1;
    }
};

//Another soln 98%
class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        unordered_map<string, int> dp;
        vector<string> v = stickers;
        sort(target.begin(), target.end());
        for (auto& a : v) {
            sort(a.begin(), a.end());
        }
        dp[""] = 0;
        getNum(target, v, dp);
        return dp[target] >= 1e6 ? -1 : dp[target];
    }

private:
    int getNum(const string& t, const vector<string>& v, unordered_map<string, int>& dp) {
        auto it = dp.find(t);
        if (it != dp.end()) {
            return it->second;
        }
        int num = 1e6;
        for (const auto& s : v) {
            if (s.find(t[0]) != -1) {
                string n;
                set_difference(t.begin(), t.end(), s.begin(), s.end(), back_inserter(n));
                num = min(num, getNum(n, v, dp));
            }
        }
        return dp[t] = ++num;
    }
};














/*
Given a non-empty string, encode the string such that its encoded length is the shortest.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being 
repeated exactly k times.

Example 1:

Input: "aaa"
Output: "aaa"
Explanation: There is no way to encode it such that it is shorter than the input string, so we do not encode it.
Example 2:

Input: "aaaaa"
Output: "5[a]"
Explanation: "5[a]" is shorter than "aaaaa" by 1 character.
Example 3:

Input: "aaaaaaaaaa"
Output: "10[a]"
Explanation: "a9[a]" or "9[a]a" are also valid solutions, both of them have the same length = 5, which is
the same as "10[a]".
Example 4:

Input: "aabcaabcd"
Output: "2[aabc]d"
Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".
Example 5:

Input: "abbbabbbcabbbabbbc"
Output: "2[2[abbb]c]"
Explanation: "abbbabbbc" occurs twice, but "abbbabbbc" can also be encoded to "2[abbb]c", so one answer
can be "2[2[abbb]c]".


*/

//DP soln1
class Solution {
private:
	vector<vector<string>> dp;
public:
	string collapse(string& s, int i, int j) {
	    string temp = s.substr(i, j - i + 1);
		auto pos = (temp+temp).find(temp, 1);
		if (pos >= temp.size()) {
		    return temp;
		}
		return to_string(temp.size()/pos) + '['+ dp[i][i+pos-1]+']';
	}

	string encode(string s) {
		int n = s.size();
		dp = vector<vector<string>>(n, vector<string>(n, ""));
		for (int step = 1; step <= n; step++) {
			for (int i = 0; i + step - 1 < n; i++) {
				int j = i + step - 1;
				dp[i][j] = s.substr(i, step);
				for (int k = i; k < j; k++) {
					auto left = dp[i][k];
					auto right = dp[k + 1][j];
					if (left.size() + right.size() < dp[i][j].size()) {
						dp[i][j] = left + right;
					}
				}
				string replace = collapse(s, i, j);
				if (replace.size() < dp[i][j].size()) {
					dp[i][j] = replace;
				}
			}
		}
		return dp[0][n - 1];
	}
};



//DP soln 94%
class Solution {
public:
    string encode(string s) {
        // 用dp[i][L]记录从i开始长为L的子串的最短编码
        const int N = s.size();
        vector<vector<string>> dp(N, vector<string>(N + 1));
        for (int L = 1; L <= N; L++) {
            for (int i = 0; i + L - 1 < N; i++) {
                dp[i][L] = collapse(s.substr(i, L), dp[i]);
                for (int k = 1; k < L; k++) { // L长分两段，第一段长k
                    if (dp[i][k].size() + dp[i+k][L-k].size() < dp[i][L].size()) {
                        dp[i][L] = dp[i][k] + dp[i+k][L-k];
                    }
                }
            }
        }
        return dp[0][N];
    }
    
    string collapse(const string &s, vector<string> &dpi) {
        int found = (s + s).find(s, 1), L = s.size();
        if (found < L) { // s=k*pattern
            auto encoded = to_string(L / found) + "[" + dpi[found] + "]"; // dp[i][found]是子问题最优解
            if (encoded.size() < L) return encoded;
        }
        return s;
    }
};


//DFS . + memoziation
class Solution {
    int numRepetition(string &s, string &t) {
        int cnt=0,i=0;
        while(i<s.length()) {
            if(s.substr(i,t.length())!=t) break;
            cnt++;
            i+=t.length();
        }
        return cnt;
    }
    string dfs(string s, unordered_map<string,string> &m) {
        if(s.length()<5) return s;
        if(m.count(s)) return m[s];
        string res = s;
        for(int i=0;i<s.length();i++) {
            string s1 = s.substr(0,i+1);
            int cnt = numRepetition(s,s1);
            string t;
            for(int k=1;k<=cnt;k++) {
                if(k==1) t=s1+dfs(s.substr(i+1),m);
                else t = to_string(k)+"["+dfs(s1,m)+"]"+dfs(s.substr(k*s1.length()),m);
                if(t.length()<res.length()) res=t;            
            }
        }
        m[s]=res;
        return res;        
    }
public:
    string encode(string s) {
        unordered_map<string,string> m;
        return dfs(s,m);
    }
};


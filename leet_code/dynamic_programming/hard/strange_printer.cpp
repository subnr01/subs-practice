/*

There is a strange printer with the following two special requirements:

The printer can only print a sequence of the same character each time.
At each turn, the printer can print new characters starting from and ending at any places, and 
will cover the original existing characters.
Given a string consists of lower English letters only, your job is to count the minimum number of
turns the printer needed in order to print it.

Example 1:
Input: "aaabbb"
Output: 2
Explanation: Print "aaa" first and then print "bbb".
Example 2:
Input: "aba"
Output: 2
Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the
existing character 'a'.
Hint: Length of the given string will not exceed 100.

*/

//Dp soln
class Solution {
public:
    int dp[107][107] ;
    pair<int,int> arr[107] ;
    
    int strangePrinter(string s) {
        int len = s.size() ;
        
        if(len == 0)
            return 0 ;
        
        int ind = 0 ;
        
        for(int i=0 ; i<len ; i++)
        {
            arr[ind] = make_pair(s[i]-'a',0);
            
            while(i<len && arr[ind].first == int(s[i] - 'a'))
                i++, arr[ind].second++ ;
            
            i--;
            ind++;
        }
        
        memset(dp,-1,sizeof(dp));
        return rec(0,ind-1)+1 ;
    }
    
    int rec(int l,int r)
    {
        if(r<=l)
            return 0 ;
        
        int& ret = dp[l][r] ;
        
        if(ret != -1)
            return ret ;
        
        ret = rec(l,r-1) + 1 ;
        
        for(int i=r-1 ; i>=l ; i--)
        {
            if(arr[i].first == arr[r].first)
                ret = min(ret,rec(l,i)+rec(i+1,r-1)+1);
        }
        
        return ret ;
    }
};




//DP soln 2
class Solution {
public:
    int strangePrinter(string s) {
        int len  = s.length();
        if (not len) return 0;
        string target = string(1, s[0]);
        for (int i=1; i<len; ++i)
        {
            if (s[i] == target.back())  continue;
            target.append(1, s[i]);
        }
        len = target.length();
        vector<vector<int>> dp(len, vector<int>(len, 1));
        for (int l=2; l<=len; ++l)
        {
            for (int i=0; i<=len-l; ++i)
            {
                int left = i, right = i+l-1;
                dp[left][right] = (target[left] == target[right] ? 0:1) + min(dp[left][right-1], dp[left+1][right]);
                char key = target[right];
                for (int j=left+1; j<right; ++j)
                {
                    if (key == target[j])
                    {
                        dp[left][right] = min(dp[left][right], dp[left][j-1] + dp[j][right]);
                    }
                }
            }
        }
        return dp[0][len-1];
    }
};

//DFS + memiozation
class Solution {
private:
    
    vector<vector<int>> dp;
    int dfs(const string& s, int st, int en) {
        if (st > en) {
            return 0;
        }
        
        if (dp[st][en] != -1) {
            return dp[st][en];
        }
        
        int f = 1 + dfs(s, st+1, en);
        for (int i = st+1; i <= en; ++i) {
            if (s[i] == s[st]) {
                f = min(f, dfs(s, st+1, i-1) + dfs(s, i, en));
            }
        }
        return dp[st][en] = f;
    }
    
public:
    int strangePrinter(string s) {
        string tmp = "";
        for (char c : s) {
            if (tmp == "" || c != tmp.back()) {
                tmp += c;
            }
        }
        dp.resize(tmp.size(), vector<int> (tmp.size(), -1));
        return dfs(tmp, 0, tmp.size()-1);
    }
};

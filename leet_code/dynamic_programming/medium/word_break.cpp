/*
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if 
s can be segmented into a space-separated sequence of one or more dictionary words. You may assume the 
dictionary does not contain duplicate words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".

*/


class Solution {
public:
 
    
    bool wordBreak(string s, vector<string>& wordDict) {
       
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        if(dict.size()==0) return false;
        
        vector<bool> dp(s.size()+1,false);
        dp[0]=true;
        
        // i is equal to or lesser than
        for(int i=1;i<=s.size();i++)
        {
            for(int j=i-1;j>=0;j--)
            {
                if(dp[j])
                {
                    string word = s.substr(j,i-j);
                    if(dict.find(word)!= dict.end())
                    {
                        //Remember it is dp[i]
                        dp[i]=true;
                        break; //next i
                    }
                }
            }
        }
        
        return dp[s.size()];
    }
};

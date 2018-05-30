/*
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. You may assume the dictionary does not contain duplicate words.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].

UPDATE (2017/1/4):

*/

class Solution {
public:
	vector<string> wordBreak(string s, vector<string>& wordDict) {
		this->s = s;
		this->dict = unordered_set<string>(wordDict.begin(), wordDict.end());
		return dfs(0);
		
	}
private:
	string s;
	unordered_set<string> dict;
	unordered_map<int, vector<string>> cache;
	vector<string> dfs(int cur)
	{
		if (cur == s.length()) return{ "" };
		vector<string> ans;
		for (int i = cur + 1; i <= s.length(); i++)
		{
			string sub = s.substr(cur, i - cur);
			if (dict.count(sub))
			{
				bool find = cache.count(i);
				vector<string>& suffix = cache[i];
				if (find == false)
					suffix = dfs(i);
				for (string str : suffix)
					ans.emplace_back(sub + (str==""? "": (" " + str) ) );
			}
		}
		return ans;
	}
};


//92% 
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int lens=s.size();
        unordered_set<string> dict;
        for(string wd : wordDict){
            dict.insert(wd);
        }
        vector<bool> dp(lens+1,false);
        dp[0]=true;
        for(int tmplen=1;tmplen<=lens;tmplen++){
            for(int j=tmplen-1;j>=0;j--){
                if(dp[j]&&dict.count(s.substr(j,tmplen-j))){
                    dp[tmplen]=true;
                    break;
                }
            }
        }
        vector<string> res;
        if(!dp[lens])return res;
        dfs(res,"",s,dict,dp,0,lens);
        return res;
    }
    void dfs(vector<string>& res,string tmps,string s,unordered_set<string>& dict,vector<bool>& dp,int start,int lens){
        if(start==lens){
            res.push_back(tmps);
        }else{
            for(int j=start+1;j<=lens;j++){
                if(dp[j]&&dict.count(s.substr(start,j-start))){
                    dfs(res,tmps+(tmps.size()>0? " ":"")+s.substr(start,j-start),s,dict,dp,j,lens);
                }
            }
        }
    }
};

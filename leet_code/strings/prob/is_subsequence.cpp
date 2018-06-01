/*
Given a string s and a string t, check if s is subsequence of t.

Example 1:
s = "abc", t = "ahbgdc"

Return true.

Example 2:
s = "axc", t = "ahbgdc"

Return false.

Follow up:
If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, and you want to check one by one to see 
if T has its subsequence. In this scenario, how would you change your code?


*/


class Solution {
public:
    bool isSubsequence(string s, string t) {
    	auto i = s.begin();
        for(char c : t) i += (*i == c);
        return i == s.end();
    }
};

For the Follow-up, assume we have S1...Sk, above C++ code can be change to a simple follow-up version:
Follow-up, O(len(t) * k)

class Solution {
public:
    vector<bool> isSubsequence(vector<string> ss, string t) {
    	vector<string::const_iterator> iters(ss.size());
    	for(int i = 0; i < ss.size(); i++) {
    		iters[i] = ss[i].begin();
    	}
        for(char c : t) {
        	for(int i = 0; i < ss.size(); i++) {
        		iters[i] += *iters[i] == c;
        	}
        }
        vector<bool> ans(ss.size());
        for(int i = 0; i < ss.size(); i++) {
        	ans[i] = iters[i] == ss[i].end();
        }
        return ans;
    }
};


//Binary search soln
class Solution {
public:
    bool isSubsequence(string s, string t) {
        //build a record the index of each char in t
        vector<vector<int>> record(26);
        //add indexs
        for(int i = 0; i < t.size(); i++) {
            record[t[i]-'a'].push_back(i);
        }
        //check if each char in s is in the legal place
        int index = -1;
        for(int i = 0; i < s.size(); i++) {
            auto iter = upper_bound(record[s[i]-'a'].begin(), record[s[i]-'a'].end(), index);
            if(iter == record[s[i]-'a'].end()) return false;
            index = *iter;
        }
        return true;
    }
};

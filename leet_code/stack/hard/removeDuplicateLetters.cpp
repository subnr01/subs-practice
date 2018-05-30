/*

Given a string which contains only lowercase letters, remove duplicate letters so that every 
letter appear once and only once. You must make sure your result is the smallest in 
lexicographical order among all possible results.

Example 1:

Input: "bcabc"
Output: "abc"
Example 2:

Input: "cbacdcbc"
Output: "acdb"

*/

//relatd topics:stack

//wihtout using stack and faster
class Solution {
public:
    string removeDuplicateLetters(string s) {
		vector<int> ht(26), ht2(26);
		for (auto c : s) ht[c-'a']++;
		string ret;
		for (auto c : s) {
			while (!ht2[c-'a'] && !ret.empty() && ht[ret.back()-'a'] && c < ret.back()) {
				ht2[ret.back()-'a'] = 0;
				ret.pop_back();
			}
			if (!ht2[c-'a']) {
				ret.push_back(c);
				ht2[c-'a'] = 1;
			}
			ht[c-'a']--;
		}
		return ret;
    }
};


//using stack
class Solution {
public:
    string removeDuplicateLetters(string s) {
        unordered_map<char, int> cnts;
        string ret;
        stack<char> stk;
        vector<bool> isVisited(26, false);
        for (char each : s) cnts[each] ++;
        for (int i = 0; i < s.size(); cnts[s[i]] --, ++ i) {
            if (isVisited[s[i] - 'a'] || (!stk.empty() && stk.top() == s[i])) continue;
            while (!stk.empty() && stk.top() > s[i] && cnts[stk.top()] > 0) {
                isVisited[stk.top() - 'a'] = false;
                stk.pop();
            }
            stk.push(s[i]);
            isVisited[s[i] - 'a'] = true;
        }
        while (!stk.empty()) {
            ret.push_back(stk.top());
            stk.pop();
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};


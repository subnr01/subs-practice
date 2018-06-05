/*
Refer leetcode for description

*/


//Related topics: String, stack



//Alexander
//https://leetcode.com/problems/tag-validator/discuss/103374/C++-Clean-Code-Recursive-Parser
class Solution {
public:
    bool isValid(string code) {
        int i = 0;
        return validTag(code, i) && i == code.size();
    }

private:
    bool validTag(string s, int& i) {
        int j = i;
        string tag = parseTagName(s, j);
        if (tag.empty()) return false;
        if (!validContent(s, j)) return false;
        int k = j + tag.size() + 2; // expecting j = pos of "</" , k = pos of '>'
        if (k >= s.size() || s.substr(j, k + 1 - j) != "</" + tag + ">") return false;
        i = k + 1;
        return true;
    }

    string parseTagName(string s, int& i) {
        if (s[i] != '<') return "";
        int j = s.find('>', i);
        if (j == string::npos || j - 1 - i < 1 || 9 < j - 1 - i) return "";
        string tag = s.substr(i + 1, j - 1 - i);
        for (char ch : tag) {
            if (ch < 'A' || 'Z' < ch) return "";
        }
        i = j + 1;
        return tag;
    }

    bool validContent(string s, int& i) {
        int j = i;
        while (j < s.size()) {
            if (!validText(s, j) && !validCData(s, j) && !validTag(s, j)) break;
        }
        i = j;
        return true;
    }

    bool validText(string s, int& i) {
        int j = i;
        while (i < s.size() && s[i] != '<') { i++; }
        return i != j;
    }

    bool validCData(string s, int& i) {
        if (s.find("<![CDATA[", i) != i) return false;
        int j = s.find("]]>", i);
        if (j == string::npos) return false;
        i = j + 3;
        return true;
    }
};


//Short soln using stack
class Solution {
public:
    bool isValid(string code) 
    {
        stack<string> stk;
	for (int i = 0; i < code.length(); i++) {        
	    if (i > 0 && stk.empty()) return false;
	    if (code.substr(i, 9) == "<![CDATA[") {
		int j = i + 9;
		i = code.find("]]>", j);
		if (i < 0) return false;
		i += 2;
            } else if (code.substr(i, 2) == "</") {
		int j = i + 2;
		i = code.find('>', j);
		string s = code.substr(j, i - j);
		if (stk.empty() || s != stk.top()) return false;
		stk.pop();
	    } else if (code.substr(i, 1) == "<") {
		int j = i + 1;
		i = code.find('>', j);
		if (i < 0 || i == j || i - j > 9) return false;
		for (int k = j; k < i; k++) {
	            if (!isupper(code[k])) return false;
		}
		string s = code.substr(j, i - j);
		stk.push(s);
            }
	}
	return stk.empty();        
    }
};

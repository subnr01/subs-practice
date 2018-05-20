/*

Given a string and a string dictionary, find the longest string in the
dictionary that can be formed by deleting some characters of the given string.
If there are more than one possible results, return the longest word with the 
smallest lexicographical order. If there is no possible result, return the empty string.

Example 1:
Input:
s = "abpcplea", d = ["ale","apple","monkey","plea"]

Output: 
"apple"
Example 2:
Input:
s = "abpcplea", d = ["a","b","c"]

Output: 
"a"
Note:
All the strings in the input will only contain lower-case letters.
The size of the dictionary won't exceed 1,000.
The length of all the strings in the input won't exceed 1,000.

*/


//With sort
class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        struct compare{
            bool operator()(string a, string b){
                if(a.size() > b.size() || (a.size() == b.size() && a < b))
                    return true;
                else
                    return false;
            }
        };
        sort(d.begin(),d.end(),compare());
        for(auto it:d)
            if(check(it,s))
                return it;
        return "";
    }
    
    bool check(string s1, string s2){
        int len1 = s1.size(), len2 = s2.size();
        if(len1 > len2)
            return false;
        int i=0,j=0;
        while(i<len1 && j<len2){
            char ch = s1[i];
            while(j<len2 && s2[j] != ch)
                j++;
            i++;
            j++;
        }
        return i == len1 && j <= len2;
    }
};



//Without sort
class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        int minDis = INT_MAX;
        string res = "";
        for (string str: d) {
            int sidx = 0, stridx = 0;
            while (sidx < s.size() && stridx < str.size()) {
                while (sidx < s.size() && s[sidx] != str[stridx]) ++sidx;
                if (sidx != s.size()) {
                    ++stridx;
                    ++sidx;
                }
            }
            if (stridx == str.size()) {
                if (s.size() - str.size() < minDis) {
                    minDis = s.size() - str.size();
                    res = str;
                }
                else if (s.size() - str.size() == minDis) {
                    res = min(res, str);
                }
            }
        }
        return res;
    }
};

//Another Soln
class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        int minDis = INT_MAX;
        string res = "";
        for (string str: d) {
            int sidx = 0, stridx = 0;
            while (sidx < s.size() && stridx < str.size()) {
                while (sidx < s.size() && s[sidx] != str[stridx]) ++sidx;
                if (sidx != s.size()) {
                    ++stridx;
                    ++sidx;
                }
            }
            if (stridx == str.size()) {
                if (s.size() - str.size() < minDis) {
                    minDis = s.size() - str.size();
                    res = str;
                }
                else if (s.size() - str.size() == minDis) {
                    res = min(res, str);
                }
            }
        }
        return res;
    }
};


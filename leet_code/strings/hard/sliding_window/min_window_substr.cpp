/*

Given a string S and a string T, find the minimum window in S which will contain all the characters
in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

*/


//Related topics: hash table, 2 pointers, string

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.size() == 0 || t.size() == 0) return "";
        vector<int> remaining(128, 0);
        int required = t.size();
        for (int i = 0; i < required; i++) remaining[t[i]]++;
        // left is the start index of the min-length substring ever found
        int min = INT_MAX, start = 0, left = 0, i = 0;
        while(i <= s.size() && start < s.size()) {
            if(required) {
                if (i == s.size()) break;
                remaining[s[i]]--;
                if (remaining[s[i]] >= 0) required--;
                i++;
            } else {
                if (i - start < min) {
                    min = i -start;
                    left = start;
                }
                remaining[s[start]]++;
                if (remaining[s[start]] > 0) required++;
                start++;
            }
        }
        return min == INT_MAX? "" : s.substr(left, min);
    }
};

//simpler???
class Solution {
public:
    string minWindow(string s, string t) {
        int n=s.size();
        int m=t.size();
        if(n<1 || m<1 || n<m)
            return string("");
        int map[255]={0};
        for(char c: t)
            map[c]--;
        
        int counter=-m;
        int begin=0;
        int end=0;
        int d=n+1;
        int head=0;
        while(end<n)
        {
            if(map[s[end]]<0)
            { 
                counter++;
            }
            map[s[end]]++;
            end++;
            
            while(counter==0)
            {
                if(d>end-begin)
                {
                    d=end-begin;
                    head=begin;
                }
                if(map[s[begin]]==0) counter--;
                map[s[begin]]--;                    
                begin++;
            }
        }
        if(d==n+1)
            return string("");
        return string(s, head, d);
    }
};


/*

Count the number of segments in a string, where a segment is defined to be a contiguous sequence 
of non-space characters.

Input: "Hello, my name is John"
Output: 5
*/


class Solution {
public:
    int countSegments(string s) {
        int res = 0;
        s.push_back(' ');
        //notice i is 1 here
        for(int i = 1; i < s.size(); ++i)
          if(s[i] == ' ' && s[i-1] != ' ') ++res;
        return res;
    }
};


/*
Another solution
*/

class Solution {
public:
    int countSegments(string s) {
        int res = 0;
        for (int i = 0; i < s.size(); i++) 
            res += s[i] != ' ' && (i + 1 == s.size() || s[i + 1] == ' ');
        return res;
    }
};

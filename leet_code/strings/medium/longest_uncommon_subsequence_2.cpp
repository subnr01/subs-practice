/*


Longest Uncommon Subsequence II


Given a list of strings, you need to find the longest uncommon subsequence among them. 
The longest uncommon subsequence is defined as the longest subsequence of one of these strings
and this subsequence should not be any subsequence of the other strings.

A subsequence is a sequence that can be derived from one sequence by deleting some characters
without changing the order of the remaining elements. Trivially, any string is a subsequence of 
itself and an empty string is a subsequence of any string.

The input will be a list of strings, and the output needs to be the length of the longest uncommon
subsequence. If the longest uncommon subsequence doesn't exist, return -1.

Example 1:
Input: "aba", "cdc", "eae"
Output: 3

*/


//Using recursion
class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        int n = strs.size();
        int maxlen = -1;
        for (int i = 0; i < n; i++) {
            bool uniq = true;
            for (int j = 0; j < n; j++) {
                if (i != j && isSubsequence(strs[i], strs[j], 0, 0)) {
                    uniq = false;
                    break;
                }
            }
            if (uniq) {
                maxlen = max(maxlen, (int)strs[i].length());
            }
        }

        return maxlen;
    }
private:
    bool isSubsequence(string s, string t, size_t si, size_t ti) {
        if (si == s.length()) {
            return true;
        }
        if (ti == t.length()) {
            return false;
        }

        return (s[si] == t[ti]) && isSubsequence(s, t, si + 1, ti + 1) || isSubsequence(s, t, si, ti + 1);
    }
};



//Using sorting (faster soln)
bool cmp(pair<string,int> &a, pair<string,int> &b)
{
    return a.first.size() > b.first.size();
}

bool isS1subsOfS2(string &s1, string &s2){
    int j = 0, i = 0;
    for(; i < s1.size(); ++i){
        while(j < s2.size() && s1[i] != s2[j]) ++j;
        if(j == s2.size())
           return false;
        ++j;
    }
    return true;
}
class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        unordered_map<string,int> m;
        //Store all the string and their counts in map
        for(int i = 0; i < strs.size(); ++i)
          ++m[strs[i]];
        vector<pair<string,int>> v;
      
        //push them into vector. Notice how
        // a map element is converted into
        // a pair object and put inside the vector.
        for(auto it = m.begin(); it != m.end(); ++it)
           v.push_back(*it);
      
        //sort in descending order of size of the string.
        sort(v.begin(),v.end(),cmp);
      
      for(int i = 0; i < v.size(); ++i)
        {
           if(v[i].second == 1){
               int j;
               for(j = 0; j < i; ++j) {
                 //we are moving from the longest strings.
                 //Check whether it is a uncommon subsequence.
                 if(isS1subsOfS2(v[i].first,v[j].first)) {
                     break;
                 }
               }
               // WE did not find any common subsequence
               if(j == i) { 
                 return v[i].first.size();
               }
           }
        }
        return -1;
    }
};

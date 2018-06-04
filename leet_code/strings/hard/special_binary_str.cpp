/*

Special binary strings are binary strings with the following two properties:

The number of 0's is equal to the number of 1's.
Every prefix of the binary string has at least as many 1's as 0's.
Given a special string S, a move consists of choosing two consecutive, non-empty, 
special substrings of S, and swapping them. (Two strings are consecutive if the 
last character of the first string is exactly one index before the first character of the second string.)

At the end of any number of moves, what is the lexicographically largest resulting string possible?

Example 1:
Input: S = "11011000"
Output: "11100100"
Explanation:
The strings "10" [occuring at S[1]] and "1100" [at S[3]] are swapped.
This is the lexicographically largest string possible after some number of swaps.

*/

//related topics: string, recursion

//Alexander
class Solution {
public:
    string makeLargestSpecial(string s) {
        int i = 0;
        return dfs(s, i);
    }

private:
    string dfs(string& s, int& i) {
        string res;
        vector<string> toks;
        while (i < s.size() && res.empty()) {
            if (s[i++] == '1') toks.push_back(dfs(s, i));
            else res += "1";
        }
        bool prefix = res.size();
        sort(toks.begin(), toks.end());
        for (auto it = toks.rbegin(); it != toks.rend(); it++) res += *it;
        if (prefix) res += '0';
        return res;
    }
};


//soln difficult to comprehend like the question
string makeLargestSpecial(string S) {
    int count = 0, i = 0;
    vector<string> res;
    for (int j = 0; j < S.size(); ++j) {
      if (S[j] == '1') count++;
      else count--;
      if (count == 0) {
        res.push_back('1' + makeLargestSpecial(S.substr(i + 1, j - i - 1)) + '0');
        i = j + 1;
      }
    }
    sort(res.begin(), res.end(), greater<string>());
    string res2 = "";
    for (int i = 0; i < res.size(); ++i) res2 += res[i];
    return res2;
  }

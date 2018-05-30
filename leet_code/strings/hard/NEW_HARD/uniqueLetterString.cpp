/*

A character is unique in string S if it occurs exactly once in it.

For example, in string S = "LETTER", the only unique characters are "L" and "R".

Let's define UNIQ(S) as the number of unique characters in string S.

For example, UNIQ("LETTER") =  2.

Given a string S with only uppercases, calculate the sum of UNIQ(substring) over all non-empty substrings of S.

If there are two or more equal substrings at different positions in S, we consider them different.

Since the answer can be very large, retrun the answer modulo 10 ^ 9 + 7.

 

Example 1:

Input: "ABC"
Output: 10
Explanation: All possible substrings are: "A","B","C","AB","BC" and "ABC".
Evey substring is composed with only unique letters.
Sum of lengths of all substring is 1 + 1 + 1 + 2 + 2 + 3 = 10
Example 2:

Input: "ABA"
Output: 8
Explanation: The same as example 1, except uni("ABA") = 1.

*/

// no distribution, check out other soln, articles possible

class Solution {
public:
    int uniqueLetterString(string S) {
        if (S.empty()) return 0;
        unsigned long long ans = 0;
        for (char c = 'A'; c <= 'Z'; ++c) {
            int idx = 0, prev = -1, next = 0;
            while (idx < S.size() && S[idx] != c) ++idx;
            if (idx == S.size()) continue;
            for (next = idx + 1; next < S.size() && S[next] != c; ++next);
            while (idx < S.size()) {
                //cout << " c = " << c << " prev = " << prev << " idx="<< idx << " next=" << next << endl;
                unsigned long long left_cnt = idx - prev, right_cnt = next - idx;
                ans = (ans + (left_cnt * right_cnt) % 1000000007) % 1000000007;
                prev = idx; idx = next;
                for (next = next + 1; next < S.size() && S[next] != c; ++next);
            }
        }
        return ans;
    }
};

/*

Maximum Swap

Given a non-negative integer, you could swap two digits at most once to get the maximum valued number. 
Return the maximum valued number you could get.

Example 1:
Input: 2736
Output: 7236
Explanation: Swap the number 2 and the number 7.
Example 2:
Input: 9973
Output: 9973
Explanation: No swap.

*/


class Solution {
public:
    int maximumSwap(int num) {
        string s = to_string(num);
        swaponce(s);
        int l = stoi(s);
        return l;
    }
private:
    void swaponce(string& s) {
        for (int i = 0; i < s.size(); i++) {
            int maxpos = i;
            for (int j = s.size() - 1; j > i; j--) {
                if (s[j] > s[maxpos]) {
                    maxpos = j;
                }
            }
            if (maxpos != i) {
                swap(s[i], s[maxpos]);
                break;
            }
        }
    }
};

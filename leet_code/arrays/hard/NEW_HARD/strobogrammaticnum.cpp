/*

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high.

Example:

Input: low = "50", high = "100"
Output: 3 
Explanation: 69, 88, and 96 are three strobogrammatic numbers.





*/

class Solution {
public:
    vector<int> FIVE = {0, 1, 6, 8, 9};
    vector<int> THREE = {0, 1, 8};
    int strobogrammaticInRange(string low, string high) {
        int ans = 0, m = low.size(), n = high.size();
        if (m > n || (m == n && low > high)) return 0;
        ans = helper(m, low, true);
        for (int i = m + 1; i <= n; ++i) {
            ans += helper(i, "", true);
        }
        return ans - helper(n, high, false);
    }
    
    int helper(int n, string lo, bool inclusive) {
        int ans = 0;
        bool same = true;
        for (int i = 0; i < n/2; i++) {
            ans *= 5;
            if (!same) continue;
            ans += (lo == "") ? 4 : count(i, lo, FIVE);
            if (lo == "" || lo[i] > '1' && lo[i] < '8' && lo[i] != '6') same = false;
        }
        if (n % 2 == 1) {
            ans *= 3;
            if (same) {
                ans += count(n/2, lo, THREE); // lo is not null. n > 1, not same; n = 1, it's low.
                if (lo[n/2] > '1' && lo[n/2] != '8') same = false;
            }
        }
        if (same) {
            string s = get(lo);
            if (s > lo || (inclusive && (s == lo))) ans++;
        }
        return ans;
    }
    
    //count digits greater than lo[i]
    int count(int i, string lo, vector<int>& arr) {
        int cnt = 0, lower = lo[i] - '0';
        for (int d : arr) {
            if (d > lower) cnt++;
        }
        return cnt;
    }
    
    //rebuild by half of str
    string get(string str) {
        int n = str.size();
        string s = str.substr(0,(n+1)/2);
        for (int i = n/2 - 1; i >= 0; --i) {
            if (str[i] == '6') s += '9';
            else if (str[i] == '9') s += '6';
            else s += str[i];
        }
        return s;
    }
};

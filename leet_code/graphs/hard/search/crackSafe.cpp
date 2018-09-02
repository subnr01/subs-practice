/*
There is a box protected by a password. The password is n digits, where each letter 
can be one of the first k digits 0, 1, ..., k-1.

You can keep inputting the password, the password will automatically be matched 
against the last n digits entered.

For example, assuming the password is "345", I can open it when I type "012345", 
but I enter a total of 6 digits.

Please return any string of minimum length that is guaranteed to open the box after the entire string is inputted.

Example 1:
Input: n = 1, k = 2
Output: "01"
Note: "10" will be accepted too.
Example 2:
Input: n = 2, k = 2
Output: "00110"
Note: "01100", "10011", "11001" will be accepted too.

*/




//CHECK OUT THE SOLNS
//Hierholzer's Algorithm and Inverse Burrows-Wheeler Transform



// Inverse Burrows-Wheeler Transform
class Solution {
public:
    string crackSafe(int n, int k) {
        // Compute the length. Total length will be s * k
        int s = 1;
        for (int i = 0; i < n - 1; ++i)
            s *= k;

        // Construct the permutation according to wiki
        std::vector<int> inds(s * k);
        for (int i = 0; i < k * s; ++i)
            inds[i] = i / s + (i % s) * k;

        std::string seq;
        for (int off = 0; off < s * k; ++off)
        {
            // Find cycles in the permutation
            int c = off, tmp = 0;
            while (inds[c] != -1)
            {
                seq.push_back(c / s + '0');
                tmp = inds[c];
                inds[c] = -1;
                c = tmp;
            }
        }

        // Need to append n - 1 more characters
        for (int i = 0; i < n - 1; ++i)
            seq.push_back(seq[i]);
        return seq;
    }
};



//DFS????
class Solution {
    bool Gene(const int n, const int k, unordered_map<string, bool>&vis, string& ans) {
        if (vis.size() == pow(k, n)) {
            return true;
        }
        for (int i = 0; i < k; ++i) {
            ans += '0' + i;
            string pwd = ans.substr(ans.length() - n);
            if (vis.find(pwd) == vis.end()) {
                vis[pwd] = 1;
                if (Gene(n, k, vis, ans)) {
                    return true;
                }
                vis.erase(pwd);
            }
            ans.pop_back();
        }
        return false;
    }
public:
    string crackSafe(int n, int k) {
        string ans = string(n, '0');
        unordered_map<string, bool>vis;
        vis[ans] = 1;
        Gene(n, k, vis, ans);
        return ans;
    }
};

/*

Palindrome Permutation II
---------------------------

Given a string s, return all the palindromic permutations (without duplicates) of it. 
Return an empty list if no palindromic permutation could be form.

For example:

Given s = "aabb", return ["abba", "baab"].

Given s = "abc", return [].
 
 */
 
 
 class Solution {
public:
    vector<string> generatePalindromes(string s) {
        vector<int> table(128);
        for (char c : s) {
            ++table[c];
        }

        vector<string> result;
        int odd = 0;
        string mid;
        string seed;
        for (int i = 0; i < table.size(); ++i) {
            if (table[i] % 2) {
                ++odd;
                mid += i;
                if (odd > 1) {
                    return result;
                }
            }
            table[i] >>= 1;
            seed += string(table[i], i);
        }
        
        string path;
        vector<bool> used(seed.size());
        dfs(seed, path, mid, used, result);
        return result;
    }

private:
    void dfs(string& seed, string& path, string mid, vector<bool>& used, vector<string>& result) {
        if (path.size() == seed.size()) {
            string rev(path);
            reverse(rev.begin(), rev.end());
            result.push_back(path + mid + rev);
            return;
        }

        for (int i = 0; i < seed.size(); ++i) {
            if (used[i]) {
                continue;
            }
            if (i > 0 && seed[i] == seed[i - 1] && !used[i - 1]) {
                continue;
            }
            used[i] = true;
            path.push_back(seed[i]);
            dfs(seed, path, mid, used, result);
            path.pop_back();
            used[i] = false;
        }
    }
};


//another Soln
class Solution {
public:
    vector<string> generatePalindromes(string s) {
        vector<string> result;
        unordered_map<char, int> charCount;
        int oddCnt=0, N=0;
        string mid;
        for (int i=0; i<s.size(); i++)
            charCount[s[i]] ++;
        for (auto &c : charCount) {
            if (c.second & 1) {
                mid = c.first;
                oddCnt++;
            }
            c.second /= 2;
            N += c.second;
        }
        if (oddCnt > 1)
            return result;
        helper(charCount, "", mid, N, result);
        return result;
    }
private:
    void helper(unordered_map<char, int> &charCount, string s, string &mid, int &N, vector<string> &r) {
        if (s.size() == N) {
            string rev = s;
            reverse(rev.begin(), rev.end());
            r.push_back(s + mid + rev);
            return;
        }
        for (auto &c : charCount) {
            if (c.second > 0) {
                c.second--;
                helper(charCount, s+c.first, mid, N, r);
                c.second++;
            }
        }
    }
};

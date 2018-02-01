/*

Palindrome Permutation II
---------------------------

Given a string s, return all the palindromic permutations (without duplicates) of it. 
Return an empty list if no palindromic permutation could be form.

For example:

Given s = "aabb", return ["abba", "baab"].

Given s = "abc", return [].
 
 */

//without backtracking, but using next_permutation function
class Solution {
public:
    vector<string> generatePalindromes(string s) {
        vector<string> palindromes;
        unordered_map<char, int> counts;
        for (char c : s) {
            counts[c]++;
        }
        
        int odd = 0;
        char mid;
        string half;
        
        for (auto p : counts) {
            if (p.second & 1) {
                odd++;
                mid = p.first;
                if (odd > 1) {
                    return palindromes;
                }
            }
            half += string(p.second / 2, p.first);
        }
        
        palindromes = permutations(half);
        
        for (string& p : palindromes) {
            string t(p);
            reverse(t.begin(), t.end());
            if (odd) {
                t = mid + t;
            }
            p += t;
        }
        return palindromes;
    }
private:
    vector<string> permutations(string& s) {
        vector<string> perms;
        string t(s);
        do {
            perms.push_back(s);
            next_permutation(s.begin(), s.end());
        } while (s != t);
        return perms;
    }
};


//using backtracking
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

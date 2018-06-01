/*

Given two strings s and t, write a function to determine if t is an anagram of s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

*/

Points to remember:

two approaches:
In the first approach, sort both the strings and compare.
In the second approach, use a hash table and increment the character in the hash table and decrement
the character of the second string in the hash table. Run a second loop and compare the elements of the hash
table. If any of them is one, then both are not anagrams.

class Solution {
public:
    bool isAnagram_hash(string s, string t) {
        if (s.length() != t.length()) return false;
        int n = s.length();
        unordered_map<char, int> counts;
        for (int i = 0; i < n; i++) {
            counts[s[i]]++;
            counts[t[i]]--;
        }
        for (auto count : counts)
            if (count.second) return false;
        return true;
    }
    
    bool isAnagram(string s, string t) { 
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t; 
    }
    
};

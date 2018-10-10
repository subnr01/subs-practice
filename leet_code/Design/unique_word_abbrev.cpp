/*
An abbreviation of a word follows the form <first letter><number><last letter>. Below are some examples of word abbreviations:
a) it                      --> it    (no abbreviation)

     1
b) d|o|g                   --> d1g

              1    1  1
     1---5----0----5--8
c) i|nternationalizatio|n  --> i18n

              1
     1---5----0
d) l|ocalizatio|n          --> l10n
Assume you have a dictionary and given a word, find whether its abbreviation is unique in the dictionary. A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.

Example: 
Given dictionary = [ "deer", "door", "cake", "card" ]

isUnique("dear") -> false
isUnique("cart") -> true
isUnique("cane") -> false
isUnique("make") -> true

Understand the problem:
The question is a little bit tricky. 
There are only 2 conditions we return true for isUnique("word")
1. The abbr does not appear in the dict. 
2. The abbr is in the dict && the word appears one and only once in the dict. 
*/


class ValidWordAbbr {
public:
    ValidWordAbbr(vector<string> dictionary) {
        for (string s : dictionary) {
            string abb = Abbr(s);
            if (mp.count(abb) && mp[abb] != s) {
                mp[abb] = "";
            }
            else {
                mp[abb] = s;
            }
        }
    }
    
    bool isUnique(string word) {
        string abb = Abbr(word);
        return !mp.count(abb) || mp[abb] == word;
    }
    
    string Abbr(string s) {
        if (s.length() <= 2) return s;
        return s[0] + to_string(s.length() - 2) + s.back();
    }
private:
    unordered_map<string, string> mp;
};

/*
Given a string, determine if a permutation of the string could form a palindrome.

For example,
"code" -> False, "aab" -> True, "carerac" -> True.

*/


//Related topics: hash table


class Solution {
public:
    bool canPermutePalindrome(string s) {
        unordered_map<char, int> myMap;
        
        int n = s.length();
        int count = 0;
        
        for (int i = 0; i < n; i++)
        {
            myMap[s[i]]++;
            if (myMap[s[i]] % 2 == 0)
            {
                count--;
            }else {
                count++;
            }
        }
        return count <= 1; 
    }
};

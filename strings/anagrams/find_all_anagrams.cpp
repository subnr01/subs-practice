/*

Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".

*/

https://discuss.leetcode.com/topic/68976/sliding-window-algorithm-template-to-solve-all-the-leetcode-substring-search-problem


public class Solution {
    public List<Integer> findAnagrams(String s, String p) {
        List<Integer> list = new ArrayList<>();
    if (s == null || s.length() == 0 || p == null || p.length() == 0) return list;
    
    int[] hash = new int[256]; //character hash
    
    //record each character in p to hash
    for (char c : p.toCharArray()) {
        hash[c]++;
    }
    //two points, initialize count to p's length
    int left = 0, right = 0, count = p.length();
    
    while (right < s.length()) {
        //move right everytime, if the character exists in p's hash, decrease the count
        //current hash value >= 1 means the character is existing in p
        if (hash[s.charAt(right)] >= 1) {
            count--;
        }
        hash[s.charAt(right)]--;
        right++;
        
        //when the count is down to 0, means we found the right anagram
        //then add window's left to result list
        if (count == 0) {
            list.add(left);
        }
        //if we find the window's size equals to p, then we have to move left (narrow the window) to find the new match window
        //++ to reset the hash because we kicked out the left
        //only increase the count if the character is in p
        //the count >= 0 indicate it was original in the hash, cuz it won't go below 0
        if (right - left == p.length() ) {
           
            if (hash[s.charAt(left)] >= 0) {
                count++;
            }
            hash[s.charAt(left)]++;
            left++;
        
        }

        
    }
        return list;
    }
}


//Simple straightforward solution using two vectors
    /* Sliding window approach to cover all substrings in s of length p.size() *
     * Time Complexity = O(s), where s = s.size()                              */
    std::vector<int> findAnagrams(std::string s, std::string p) {
        std::vector<int> smap(26, 0), pmap(26, 0); /* since only a-z allowed   */
        std::vector<int> ans;                      /* output vector            */
        /* Handle corner cases first */
        if(s.size() == 0 || p.size() == 0 || s.size() < p.size()) return ans;
        /* Add all chars in p and first p.size() chars of s into a table */
        for(size_t i = 0; i < p.size(); ++i) {
            pmap[p[i] - 'a']++;
            smap[s[i] - 'a']++;
        }
        /* Sliding window to cover all substrings in s of size p           */
        for(size_t b = 0, e = b + p.size() - 1; e < s.size(); ++b, ++e) {
            if(b != 0) { /* If not first window, remove prev b and add e   */
                smap[s[b-1] - 'a']--;
                smap[s[e]   - 'a']++;
            }
            if(smap == pmap) ans.push_back(b); /* found anagram, add to ans */
        }
        return ans;
    }


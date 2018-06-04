/*

Given a string S and a string T, find the minimum window in S which will contain all the characters
in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

*/


//Related topics: hash table, 2 pointers, string

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.size() == 0 || t.size() == 0) {
            return "";
        }
        
        vector<int> remaining(128, 0);
        int required = t.size();
        for (int i = 0; i < required; i++) 
        { 
            remaining[t[i]]++;
        }
        
        // left is the start index of the min-length substring ever found
        int min = INT_MAX; 
        int start = 0; 
        int left = 0;
        int i = 0;
        
        /*
        we have to compare against equal to size 
        because the difference in distance is calculated
        at the next index, so min = i - start will give
        us the right value. If i is at the end of the string, 
        then i has to move 1 character past the end to 
        calcualte the min
        */
        while(i <= s.size()) 
        {
            if (required) 
            {
                if (i == s.size()){
                    break;
                }
                
                remaining[s[i]]--;
                if (remaining[s[i]] >= 0) { 
                    required--;
                }
                i++;
            } else {
                /*
                Point to be noted here.
                i is not moving, only start
                moves in this block
                */
                if (i - start < min) {
                    min = i - start;
                    left = start;
                }
                remaining[s[start]]++;
                /*
                Other characters in s, will be at -1, 
                so required will not get incremented for
                charcaters not in t
                */
                if (remaining[s[start]] > 0) {
                    required++;
                }
                start++;
            }
        }
        
        return min == INT_MAX? "" : s.substr(left, min);
    }
};


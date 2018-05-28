/*

Given an integer n, find the closest integer (not including itself), which is a palindrome.

The 'closest' is defined as absolute difference minimized between two integers.

Example 1:
Input: "123"
Output: "121"

*/

//Related topics: string



//
class Solution {
public:
    string nearestPalindromic(string n) {
    
        int sz = n.size();
        
        int a  = pow(10, sz) + 1;
        int b =  pow(10, sz-1) - 1;
        
        set<long> candidates;
        
        candidates.insert(a);
        candidates.insert(b);
        
        int prefix = stol(n.substr(0,(sz+1)/2));
        
        
        for(int i = -1; i <=1; i++)
        {
            string p = to_string(prefix + i);
            string pp = p + string(p.rbegin() + (sz&1), p.rend());
            
            candidates.insert(stol(pp));
        }
        
        long val = stol(n);
        long mindiff = LONG_MAX;
        long minval = LONG_MAX;
        candidates.erase(val);
        
        for (auto x:candidates)
        {
            long diff = abs(val - x);
            
            if(diff < mindiff)
            {
                mindiff=diff;
                minval=x;
                
            }else if (diff == mindiff) {
                minval = min(minval,x);
            }
            
        }
        
        return to_string(minval);
    }
    
};

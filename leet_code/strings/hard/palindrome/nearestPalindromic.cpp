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
        
        /*
        we need this because of inputs such as 10, 99.
        for 10, we must get ouput as 9, not 11 and
        for 99 we must get output as 101 and not 88,
        */
        
        candidates.insert(a);
        /*
        we need b especially as it goes down a digit, whereas
        our main logic below divides the gives input into half
        and hence obtains palindoromes of the same size,but not size - 1
        */
        candidates.insert(b);
        
        
        // find the mid "n" digits: 
        // for 121, it is 12
        // for 1234 it is 12
        // for 12345 it is 123
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
        /*
        we need the below statement becuase for
        inputs like 11, 999 we will add the same
        number based on our main logic into 
        the set 
        */
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

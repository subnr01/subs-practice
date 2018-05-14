/*

A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.

*/

//TAKE A LOOK AT OTHER SOLNs, Need to understand how 
// this is mapped to Fibonacci series
//related topics: dynamic programming

Fibonacci
F(n) = F(n-1) + F(n-2);
where F(0) and F(1) = 1;
The series becomes:
1, 1, 2, 3, 5, 8, 13, 21,


class Solution {
public:
    int numDecodings(string s) {
        
        if (s.size () == 0 || s[0] == '0') {
            return 0;
        }
        if (s.size () == 1) {
            return 1;
        }
        int num = 0;
        int m1 = 1;
        int m2 = 1;
        int count;
        bool found = false;
        for (int i = 1; i < s.size(); i++)
        {
            //REMEBER TO SET NUM TO ZERO HERE
            // num should be zero for every iteration of
            // the loop.
            num = 0;
            if (isValid(s[i])) {
                found = true;
                num = m1;
            }
            if (isValid(s[i-1], s[i])) {
                found = true;
                num += m2;
            }
            if (!found) {
                return 0;
            } else {
                m2 = m1;
                m1 = num;
                
            }
        }
        return num;
    }
    
    int isValid(const char ch)
    {
        //return ch != 0;
        int num = ch - '0';
        return (num > 0 && num <= 26);
        
    }
    
    int isValid(const char a, const char b)
    {
        if (a == '1' || a == '2' && b <= '6') {
            return true;
        }
        return false;
    }
    
};



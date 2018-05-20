/*
Given a string containing only three types of characters: '(', ')' and '*', write a function 
to check whether this string is valid. We define the validity of a string by these rules:

Any left parenthesis '(' must have a corresponding right parenthesis ')'.
Any right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.
An empty string is also valid.

Example 1:
Input: "()"
Output: True

Example 2:
Input: "(*)"
Output: True

Example 3:
Input: "(*))"
Output: True

*/

/* Test cases
(), )), ((, ***, *), (*
*/


class Solution {
public:
    bool checkValidString(string s) {
        if ( s.size() == 0) {
            return true;
        }
        int low = 0;
        int high = 0;
        for (char c: s) {
            switch (c) {
                case '(': low++, high++; break;
                case ')': low--, high--;break;
                default: low--; high++; break;
                    
            }
            // condition to ensure order
            if (high < 0) 
            {
                return false;
            }
            
            //if there were only "*"
            low  = max (low, 0);
        }
        return low == 0;
    }
};

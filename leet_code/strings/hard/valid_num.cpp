/*

Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true

*/


class Solution { 
public:
    bool isNumber(string s) {
        int i = 0, n = s.length();
        // Skip the leading spaces
        while (i < n && isspace(s[i])) i++;
        // Skip the sign
        if (s[i] == '+' || s[i] == '-') i++;
        // Check for the following significant parts
        int digits = 0, dots = 0;
        while (i < n && (isdigit(s[i]) || s[i] == '.')) { 
            if (isdigit(s[i])) digits++;
            else dots++;
            i++;
        }
        if (digits < 1 || dots > 1) return false;
        if (i == n) return true;
        // Check for the exponential parts
        if (s[i] == 'e') {
            i++;
            if (i == n) return false;
            if (s[i] == '+' || s[i] == '-') i++;
            digits = 0;
            while (i < n && (isdigit(s[i]))) {
                digits++;
                i++;
            }
            if (digits < 1) return false;
        }
        // Skip the trailing spaces
        while (i < n && isspace(s[i])) i++;
        return i == n;
    }
};

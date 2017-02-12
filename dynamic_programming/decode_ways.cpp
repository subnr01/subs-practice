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


class Solution {
public:
    int numDecodings(string s) {
    int n = s.size();
    if ( n == 0 || s[0] == '0' ) return 0;
    if ( n == 1 ) return 1;
    int m1 = 1, m2 = 1, num;
    for ( int i = 1; i < n; i++ ) {
        num = 0;
        if ( !isValid(s[i]) && !isValid(s[i-1], s[i]) ) return 0;
        if ( isValid(s[i]) ) num = m1;
        if ( isValid(s[i-1], s[i]) ) num += m2;
        m2 = m1;
        m1 = num;
    }
    return num;
}

bool isValid(char a,char b){
    return a == '1'||(a == '2' && b <='6');
}
bool isValid(char a){
    return a != '0';
}
};

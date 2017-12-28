/*
Give a string s, count the number of non-empty (contiguous) substrings that have the same number of 0's and 1's, and all the 0's and
all the 1's in these substrings are grouped consecutively.

Substrings that occur multiple times are counted the number of times they occur.

Example 1:
Input: "00110011"
Output: 6
Explanation: There are 6 substrings that have equal number of consecutive 1's and 0's: "0011", "01", "1100", 
"10", "0011", and "01".

Notice that some of these substrings repeat and are counted the number of times they occur.

Also, "00110011" is not a valid substring because all the 0's (and 1's) are not grouped together.
*/



int countBinarySubstrings(string s) {
    size_t sz = s.size();
    int curlen = 1;
    int prevlen = 0;
    int res = 0;
    
    for(int i = 1; i < sz; i++){
        if(s[i-1] == s[i]) {
            curlen++;
        } else {
            //notice prevlen is updated only
            //when the prev character does not match.
            prevlen = curlen;
            curlen = 1;
            
        }
        // we will always enter the below
        // if condition in the case
        // of a non-match. 
        if(prevlen >= curlen) {
            res++;
        }
        
    }
    return res;
}

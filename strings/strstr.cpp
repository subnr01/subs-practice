/*

Implement strstr

*/


/*

This is brute force.
There may be better versions available.
especially by 1331r
*/


class Solution {
public: 
    int strStr(string haystack, string needle)
    {
        int m = haystack.length();
        int n = needle.length();
        int j;
        
        if (!n) {
            return 0;
        }
        
        for (int i = 0; i < m - n + 1; i++) {
            
            for ( j = 0; j < n; j++) {
                if (haystack[i + j] != needle[j])
                    break;
            }
            if (j == n) return i;
        }
        return -1;
    }
};

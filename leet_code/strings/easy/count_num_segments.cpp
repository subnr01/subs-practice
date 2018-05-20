/*

Count the number of segments in a string, where a segment is defined to be a contiguous sequence 
of non-space characters.

Input: "Hello, my name is John"
Output: 5
*/


class Solution {
public:
    int countSegments(string s) {
        int len = s.size();
        int res = 0;
        
        for (int i = 0; i < len; i++)
        {
            /*
             the current letter must not be space
             and the next letter can be space or the
             next letter is eof
            */
            if (s[i] != ' ' &&
               (i + 1 == len ||
                s[i + 1] == ' '))
            {
                res++;
            }
        }
        return res;
    }
};

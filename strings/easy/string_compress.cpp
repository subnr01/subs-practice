/*
Given an array of characters, compress it in-place.

The length after compression must always be smaller than or equal to the original array.

Every element of the array should be a character (not int) of length 1.

After you are done modifying the input array in-place, return the new length of the array.

Could you solve it using only O(1) extra space?

Example 1:
Input:
["a","a","b","b","c","c","c"]

Output:
Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]

Explanation:
"aa" is replaced by "a2". "bb" is replaced by "b2". "ccc" is replaced by "c3".

Example 3:
Input:
["a","b","b","b","b","b","b","b","b","b","b","b","b"]

Output:
Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].

Explanation:
Since the character "a" does not repeat, it is not compressed. "bbbbbbbbbbbb" is replaced by "b12".
Notice each digit has it's own entry in the array.


Example 2:
Input:
["a"]

Output:
Return 1, and the first 1 characters of the input array should be: ["a"]

Explanation:
Nothing is replaced.
*/


class Solution {
public:
    int compress(vector<char> &chars) {
    int length = 0;
    int count = 0;
    for(int i = 0; i < chars.size(); i++) {
        count++;
        if(chars[i] != chars[i+1] || i == chars.size()-1) {
            chars[length++] = chars[i];
            if (count != 1) {
                string temp = to_string(count);
                // we need a for loop because, count may be more than a singel digit
                for(int j = 0; j < temp.size(); j++) {
                    chars[length++] = temp[j];
                }
                
            }
            count = 0;
        }
    }
        return length;
  }
};

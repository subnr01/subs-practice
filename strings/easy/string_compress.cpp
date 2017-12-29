/*
Given an array of characters, compress it in-place.

The length after compression must always be smaller than or equal to the original array.

Every element of the array should be a character (not int) of length 1.

After you are done modifying the input array in-place, return the new length of the array.

Could you solve it using only O(1) extra space?
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

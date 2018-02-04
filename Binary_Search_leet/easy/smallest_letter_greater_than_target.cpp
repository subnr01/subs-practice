/*
Given a list of sorted characters letters containing only lowercase letters, and given a target
letter target, find the smallest element in the list that is larger than the given target.

Letters also wrap around. For example, if the target is target = 'z' and letters = ['a', 'b'], the answer is 'a'.

Examples:
Input:
letters = ["c", "f", "j"]
target = "a"
Output: "c"

Input:
letters = ["c", "f", "j"]
target = "c"
Output: "f"

Input:
letters = ["c", "f", "j"]
target = "d"
Output: "f"

Input:
letters = ["c", "f", "j"]
target = "g"
Output: "j"

Input:
letters = ["c", "f", "j"]
target = "j"
Output: "c"

Input:
letters = ["c", "f", "j"]
target = "k"
Output: "c"


*/


class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int n = letters.size();
        
        if (n > 0 && target >= letters.back()) {
            return letters.front();
        }
        
        int low = 0;
        int high = n - 1;
        
        
        //remember (0 + 1)/2 = 0
        
        //Low is not equal to high in this case
        while(low < high)
        {
            int mid = (low + high)/2;
            
            if (letters[mid] > target)
            {
                high = mid ;
            } 
            // we cannot have a seperate block for
            // "=" as mid + 1 can be the same number.
            
            else if (letters[mid] <= target) { 
                low = mid + 1;
            } 
           
        }
        
        return letters[low];
    }
};

/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to determine if a number is strobogrammatic. The number is represented as a string.

For example, the numbers "69", "88", and "818" are all strobogrammatic.


*/





class Solution {
public:
    bool isStrobogrammatic(string num) {
        int n = num.length();
        int low = 0;
        int high = n - 1;
        unordered_map<char, char> myMap = {{'0','0'}, {'1','1'}, {'6','9'}, {'9', '6'}, {'8', '8'}};
        
        while(low <= high)
        {
            if (myMap.find(num[low]) == myMap.end() || myMap[num[low]] != num[high])
            {
                return false;
            }
            low++;
            high--;
        }
        
        return true;
    }
    
};



/*

Given an array of integers, find if the array contains any duplicates. Your function should return 
true if any value appears at least twice in the array, and it should return false if every element is distinct.

*/



class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        
        std::set<int> myset;
        std::set<int>::iterator it;
        int n = nums.size();
        int i = 0;
        
        for(i=0; i<n; i++) {
            if(myset.find(nums[i]) != myset.end()) {
                return true;
            } else {
                myset.insert(nums[i]);
            }
            
        }
        
        return false;
        
        
    }
};

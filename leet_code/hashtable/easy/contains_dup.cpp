/*
Given an array of integers, find if the array contains any duplicates. 
Your function should return true if any value appears at least twice in the array, 
and it should return false if every element is distinct.

*/


class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        if (nums.empty()) { return false; }
        unordered_map<int,int> mp;
        for (int i : nums) {
            if (++mp[i] > 1) {
                return true;
            }
        }
        return false;
    }
};


//Another solution

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        int* numList = new int [nums.size()];
        for(int i = 0; i < nums.size(); i++)
        {
            numList[i] = nums[i];
        }
        sort(numList, numList + nums.size());
        
        for(int i = 1; i < nums.size(); i++)
        {
            if(numList[i] == numList[i - 1]) return true;
        }
        return false;
    }
};

/*
Given an array of integers and an integer k, 
find out whether there are two distinct indices i and j in the array 
such that nums[i] = nums[j] and the difference between i and j is at most k.
*/


class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k)
    {
       unordered_set<int> s;

       if (k <= 0) return false;
       if (k >= nums.size()) k = nums.size() - 1;

       for (int i = 0; i < nums.size(); i++)
       {
           if (i > k) s.erase(nums[i - k - 1]);
           if (s.find(nums[i]) != s.end()) return true;
           s.insert(nums[i]);
       }

       return false;
    }
};




/*

Degree of an array:

Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum
frequency of any one of its elements.

Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.

Example 1:
Input: [1, 2, 2, 3, 1]
Output: 2
Explanation: 
The input array has a degree of 2 because both elements 1 and 2 appear twice.
Of the subarrays that have the same degree:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
The shortest length is 2. So return 2.

Example 2:
Input: [1,2,2,3,1,4,2]
Output: 6

*/


int findShortestSubArray(vector<int>& nums) 
    {
        int len = nums.size();
        unordered_map<int, vector<int>> m;
        
        for (int i = 0; i < len; i++)
        {
            m[nums[i]].push_back(i);
        }
        
        int degree = 0;
        for (auto elem: m)
        {
            int sz = elem.second.size();
            degree = max(degree, sz);
        }
        
        int shortest = INT_MAX;
        
        for (auto elem: m)
        {
            if (elem.second.size() == degree) {
                int len = elem.second.back() - elem.second[0] + 1;
                shortest = min(shortest, len);
            }
        }
        
        return shortest;
    }

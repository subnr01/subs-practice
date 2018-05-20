/*
Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].

Note:
Each element in the result should appear as many times as it shows in both arrays.
The result can be in any order.
Follow up:
What if the given array is already sorted? How would you optimize your algorithm?
What if nums1's size is small compared to nums2's size? Which algorithm is better?
What if elements of nums2 are stored on disk, and the memory is limited such that you cannot 
load all elements into the memory at once?



*/



/*

What if elements of nums2 are stored on disk, and the memory is
limited such that you cannot load all elements into the memory at
once?

If only nums2 cannot fit in memory, put all elements of nums1 into a HashMap, read 
chunks of array that fit into the memory, and record the intersections.

If both nums1 and nums2 are so huge that neither fit into the memory, sort 
them individually (external sort), then read 2 elements from each array at a time in memory, 
record intersections.


http://faculty.simpson.edu/lydia.sinapova/www/cmsc250/LN250_Weiss/L17-ExternalSortEX2.htm


*/


class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int L = 0, R = 0;
        vector<int> ans;
        while (L < nums1.size() && R < nums2.size())
        {
            if (nums1[L] == nums2[R])
            {
                ans.push_back(nums1[L]);
                L++; R++;
            }
            else if (nums1[L] > nums2[R]) R++;
            else L++;
        }
        return ans;
    }
};


//Soln with hashmap
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {

        unordered_map<int,int> map;
        vector<int> result;

        for(int i=0;i<nums1.size();i++)
        {
            map[nums1[i]]++;
        }

        for(int i=0;i<nums2.size();i++)
        {
            if(map[nums2[i]] > 0)
            {
                result.push_back(nums2[i]);
                map[nums2[i]] -= 1;
            }
        }

        return result;

    }
};

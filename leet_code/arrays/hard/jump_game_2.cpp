/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

For example:
Given array A = [2,3,1,1,4]

The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, 
then 3 steps to the last index.)

*/
//https://discuss.leetcode.com/topic/18815/10-lines-c-16ms-python-bfs-solutions-with-explanations

//Related topics: array, greedy

//faster
class Solution {
public:
    int jump(vector<int>& nums) {
        if(nums.size() < 2) return 0;
        int step = 0, last = 0, reach = 0;
        for(int i = 0; i < nums.size(); i++)
        {
            if(i > last)
            {
                step++;
                last = reach;
                if(last >= nums.size() - 1)
                    return step;
            }
            reach = max(reach, nums[i] + i);
        }
        return step;
    }
};


//fighter
class Solution {
public:
    int jump(vector<int>& nums) 
    {
        int len = nums.size();
        
        int start = 0;
        int end = 0; //end index
        int res = 0;
        while(end < len-1)
        {
            int far = 0;
            for(int i=start; i<=end; i++)
            {
                far = max(i+nums[i], far);
            }
            res++;
            start = end+1;
            end = far;
        }
        
        return res;
    }
};

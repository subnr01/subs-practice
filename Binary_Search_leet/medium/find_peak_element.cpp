 
/*
A peak element is an element that is greater than its neighbors.

Given an input array where num[i] ≠ num[i+1], find a peak element and return its index.

The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.

You may imagine that num[-1] = num[n] = -∞.

For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.

*/
 
//7 ms
class Solution {
public:
    int findPeakElement(const vector<int> &num) 
    {
        int low = 0;
        int high = num.size()-1;
        
        while(low < high)
        {
            int mid1 = (low+high)/2;
            int mid2 = mid1+1;
            if(num[mid1] < num[mid2])
                low = mid2;
            else
                high = mid1;
        }
        return low;
    }
};

//6 ms
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        
        
        int n = nums.size();
        
        if(nums.size()<2) return 0; //index 
        
        
        if(nums[0]>nums[1]) return 0;
        
        if(nums[n-1]>nums[n-2]) return n-1;
        
        for(int i=1; i<nums.size()-1; i++) {
            
            if(nums[i]>nums[i-1] && nums[i]>nums[i+1])
                return i;
        }
        
    }
};

  
//3 ms
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.size()==1)
            return 0;
        vector<int> diff;
        for(int i=0; i<nums.size()-1;i++){
            diff.push_back(nums[i]-nums[i+1]);
        }
        if (diff[0] > 0)
            return 0;
        for (int i=1; i<diff.size(); i++)
            if (diff[i-1]<0 && diff[i]>0)
                return i;
        if (diff.back()<0)
            return diff.size();
        return -1;
    }
};

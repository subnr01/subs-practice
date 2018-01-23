/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. 
Return the sum of the three integers. You may assume that each input would have exactly one solution.

    For example, given array S = {-1 2 1 -4}, and target = 1.

    The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).


*/


class Solution {
public:
    int threeSumClosest(vector<int>& a, int target) {
        int n = a.size();
        int closest = a[0] + a[1] + a[2];
        sort(a.begin(), a.end());
        int ans;
        
        for (int i = 0; i < n - 2; i++) {
            if (i != 0 && a[i] == a[i-1]) {
                continue;
            } 
            
            int j = i + 1;
            int k = n - 1;
            while (j < k) 
            {
                int sum = a[i] + a[j] + a[k];
                if (sum == target) {
                    return sum;
                }
                
                if (sum < target) {
                    j++;
                } 
                else  {
                    k--;
                }
                
                if (abs(target - sum) < abs(target - closest)) 
                {
                    closest = sum;
                }
                
            }
            
        }
        return closest;
    }
};

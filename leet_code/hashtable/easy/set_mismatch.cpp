/*
The set S originally contains numbers from 1 to n. But unfortunately, due to the data error, 
one of the numbers in the set got duplicated to another number in the set, which results in 
repetition of one number and loss of another number.

Given an array nums representing the data status of this set after the error. Your task is to
firstly find the number occurs twice and then find the number that is missing. Return them in the form of an array.

Example 1:
Input: nums = [1,2,2,4]
Output: [2,3]


*/


//Pay attention to the below test cases
/[1,1] and [2,2]

//LOOK at the XOR solutions


//Using map (my soln) TC: O(N) AND SC: O(N)
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int n = nums.size();
        vector<int> res;
        int dup = 0;
        int missing = 0;
        unordered_map<int, int> map;
        
        for (int i = 0; i < n; i++)
        {
            map[nums[i]]++;
        }
        
        for (int i = 1; i <= n; i++)
        {
            if(map[i] == 2) {
                dup = i;
            } else if(map[i] == 0) {
                missing = i;
            }
        }
        
        res.push_back(dup);
        res.push_back(missing);
        return res;
        
    }
};

//ANOTHER EVERY GOOD SOLN (LIKE THE FIRST MISSING NUMBER)
vector<int> findErrorNums(vector<int>& nums) {
        for(int i = 0; i<nums.size(); i++){
            while(nums[i] != nums[nums[i] - 1])swap(nums[i], nums[nums[i] - 1]);
        }
        for(int i = 0; i<nums.size() ; i++){
            if(nums[i] != i + 1)return {nums[i], i + 1};
        }
    }

//Using sort
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int n = nums.size();
        vector<int> res;
        int missing = 1;
        
        sort(nums.begin(), nums.end());
        
        for (int i = 1; i < n; i++)
        {
            if (nums[i] == nums[i-1]) {
                res.push_back(nums[i]);
            }
            else if (nums[i] > nums[i-1] + 1) {
                missing = nums[i-1] + 1;
            }
        }
        
        missing = (nums[n-1] != n) ?  n: missing;
        res.push_back(missing);
        return res;
        
    }
};

//xor soln
public class Solution {
    public int[] findErrorNums(int[] nums) {
        int xor = 0, xor0 = 0, xor1 = 0;
        for (int n: nums)
            xor ^= n;
        for (int i = 1; i <= nums.length; i++)
            xor ^= i;
        int rightmostbit = xor & ~(xor - 1);
        for (int n: nums) {
            if ((n & rightmostbit) != 0)
                xor1 ^= n;
            else
                xor0 ^= n;
        }
        for (int i = 1; i <= nums.length; i++) {
            if ((i & rightmostbit) != 0)
                xor1 ^= i;
            else
                xor0 ^= i;
        }
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == xor0)
                return new int[]{xor0, xor1};
        }
        return new int[]{xor1, xor0};
    }
}

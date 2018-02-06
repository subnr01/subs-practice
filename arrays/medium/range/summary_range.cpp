/*
  Given a sorted integer array without duplicates, return the summary of its ranges.
For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].
*/

//my soln
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        int start = 0;
        int end =  0;
        string s;
        vector<string> res;
        int n = nums.size();
        int i = 0;
        while (i < n)
        {
            start = i;
            while(i != n - 1  && nums[i + 1] == nums[i] + 1) {
                i++;
            }
            string s = to_string(nums[start]);
            if (start != i) {    
                end = i;
                s += "->" + to_string(nums[end]);
            } 
            i++;
            
            res.push_back(s);
        }
        return res;
        
    }
};

/*
  Given a sorted integer array without duplicates, return the summary of its ranges.
For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"].
*/


class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
    int n = nums.size();
    vector<string> res;
    int i = 0;
    bool consecutive = false;
    while(i<n){
        res.push_back(to_string(nums[i]));
        int j = i+1;
        while(j<n && nums[j]==nums[j-1]+1) {
            ++j;
            consecutive = true;
        }
        
        //more than one consecutive number
        if(consecutive){
            res.back()+="->"+to_string(nums[j-1]);
            consecutive = false;
        } 
        
        
        i=j;
        
    }
    return res;
}
};

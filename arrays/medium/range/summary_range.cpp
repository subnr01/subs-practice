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
            // we are using (j-1) here and not j.
            res.back()+="->"+to_string(nums[j-1]);
            consecutive = false;
        } 
        
        //i is not incremented, this is a while loop
        i = j;
        
    }
    return res;
}
};

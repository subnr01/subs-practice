
/*

Longest consecutive sequence

*/

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
For example, Given [100, 4, 200, 1, 3, 2], The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

//very fast
int longestConsecutive(const vector<int> &num) {
          unordered_map<int, bool> used;
          for (auto i : num) used[i] = false;
          int longest = 0;
          for (auto i : num) {
              if (used[i]) continue;
              int length = 1;
              used[i] = true;
              for (int j = i + 1; used.find(j) != used.end(); ++j) {   //Find consecutive numbers after i till search ends in failure
                  used[j] = true;
++length; }
              for (int j = i - 1; used.find(j) != used.end(); --j) {   //Find consecutive numbers before i till search ends in failure
                  used[j] = true;
++length; }
              longest = max(longest, length);
          }
          return longest;
      }
};

//Using sort instead of map
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        
        if(nums.size() == 0)
            return 0;
        
        int currentCons = 1;
        int longestCons = 1;
        
        sort(nums.begin(), nums.end());
        
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] != nums[i+1]){
                if(nums[i]+1 == nums[i+1])
                    currentCons ++;
                else {
                    if(currentCons > longestCons)
                        longestCons = currentCons;
                    currentCons = 1;
                }
            }
        }
        if(currentCons > longestCons)
            longestCons = currentCons;
        
        return longestCons;
    }
};

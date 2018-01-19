/*

Given a sorted integer array where the range of elements are in the inclusive range [lower, upper], 
return its missing ranges.

For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"].
*/


class Solution {
    public:
        vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
            vector<string> ranges;
            int next = lower;
            for (int i = 0; i < nums.size(); i++ ) {
                //if (nums[i] < next)  continue;
                if (nums[i] == next) {
                    next ++;
                    continue;
                }
                ranges.push_back(getRange(next, nums[i] - 1));
                next = nums[i] + 1;
            }
            if(next <= upper)  ranges.push_back(getRange(next, upper));
            return ranges;
        }
        
        string getRange(const int lower, const int upper) {
            if (lower == upper) {
                return to_string(lower);
            } else {
                return to_string(lower) + "->" + to_string(upper);
            }
        }
    };

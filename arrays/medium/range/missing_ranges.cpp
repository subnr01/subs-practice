/*

Given a sorted integer array where the range of elements are in the inclusive range [lower, upper], 
return its missing ranges.

For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"].
*/


class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> res;
        
        for (int n : nums) {
            
            if (n == INT_MIN) {
                lower = n + 1; 
                continue;
            }
            
            if (lower == n - 1) {
                res.push_back(to_string(lower));
            }
            else if (lower < n - 1)  {
                string s = to_string(lower) + "->" + to_string(n - 1);
                res.push_back(s);  
            }  
            
            if (n == INT_MAX) {
                 return res;
            }
            
            lower = n + 1;
        }
        
        if (lower == upper) { 
            res.push_back(to_string(upper));
        }
        else if (lower < upper)  {
          res.push_back(to_string(lower) + "->" + to_string(upper));  
        } 
        return res;
    }
};

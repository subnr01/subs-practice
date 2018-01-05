/*

Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all
unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

For example, given array S = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& a) {
       
        vector<vector<int>> result;
        sort(a.begin(), a.end());
        for (auto i = 0; i < a.size(); i++) {
            if (i != 0 && a[i] == a[i-1]) {
                continue;
            }
           
            auto j = i+1;
            auto k = a.size()-1;
            while(j<k) {
                if (a[i] + a[j] + a[k] == 0) {
                    vector<int>ans{a[i],a[j],a[k]};
                    result.push_back(ans);
                    j++; k--;
                    
                    while (j< k && a[j]==a[j-1]) {
                        j++;
                    }
                    while (j< k && a[k]==a[k+1]) {
                        k--;
                    }
                }
                else if (a[i] + a[j] + a[k] < 0) {
                    j++;
                } else
                {
                   k--;
                }
                
            }
             
            
        }
        return result;
    }
};

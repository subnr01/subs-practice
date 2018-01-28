/*
Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].

*/

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {

        unordered_map<int,int> map;
        vector<int> result;

        for(int i=0;i<nums1.size();i++)
        {
            map[nums1[i]]++;
        }

        for(int i=0;i<nums2.size();i++)
        {
            if(map[nums2[i]] > 0)
            {
                result.push_back(nums2[i]);
                map[nums2[i]] = 0;
            }
        }

        return result;

    }
};


//using set
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        set<int> res, st(nums1.begin(), nums1.end());
        
        for(int i = 0; i < nums2.size(); ++i){
            if(st.count(nums2[i])) {
                res.insert(nums2[i]);
            }
        }
        
        return vector<int> (res.begin(), res.end());
    }
};

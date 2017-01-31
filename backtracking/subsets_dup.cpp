/*

Given a collection of integers that might contain duplicates, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:

[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]

*/

class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        vector<vector<int> > totalset = {{}};
        sort(S.begin(),S.end());
        for(int i=0; i<S.size();){
            int count = 0; // num of elements are the same
            while(count + i<S.size() && S[count+i]==S[i])  count++;
            int previousN = totalset.size();
            for(int k=0; k<previousN; k++){
                vector<int> instance = totalset[k];
                for(int j=0; j<count; j++){
                    instance.push_back(S[i]);
                    totalset.push_back(instance);
                }
            }
            i += count;
        }
        return totalset;
        }
};


/* Recursive solution */

class Solution {
public:
    std::vector<std::vector<int> > subsetsWithDup(std::vector<int> &nums) {
		std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int> > res;
		std::vector<int> vec;
		subsetsWithDup(res, nums, vec, 0);
		return res;
    }
private:
	void subsetsWithDup(std::vector<std::vector<int> > &res, std::vector<int> &nums, std::vector<int> &vec, int begin) {
		res.push_back(vec);
		for (int i = begin; i != nums.size(); ++i)
			if (i == begin || nums[i] != nums[i - 1]) { 
				vec.push_back(nums[i]);
				subsetsWithDup(res, nums, vec, i + 1);
				vec.pop_back();
			}
	}
};


//Subsets without duplicates
/*
This is a good example of backtracking.
If the input is {1,2,3}, then the output looks like this:
{ {}, {1}, {1,2}, {1,2,3}, {1,3}, {2}, {2,3}, {3} }

if you see above, we back track after reaching (1,2,3),
then go back to (1,2) and make it (1,3) and so on.
*/


class Solution {
public:
    std::vector<std::vector<int> > subsets(std::vector<int> &nums) {
		std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int> > res;
		std::vector<int> vec;
		subsets(res, nums, vec, 0);
		return res;
    }
private:
	void subsets(std::vector<std::vector<int> > &res, std::vector<int> &nums, std::vector<int> &vec, int begin) {
		res.push_back(vec);
		for (int i = begin; i != nums.size(); ++i) {
			vec.push_back(nums[i]);
			subsets(res, nums, vec, i + 1);
			vec.pop_back();
		}
	}
};

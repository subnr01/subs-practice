/*

countSmaller

*/

//mergeSort solution
class Solution {
public:
    vector<int> indices;
    vector<int> buf;
    vector<int> ans;

    void mergesort(vector<int>& nums, int left, int right) {
        if (left >= right - 1) return;
        
        int mid = (left + right) / 2;
        mergesort(nums, left, mid);
        mergesort(nums, mid, right);
        
        // merge
        int idx1 = left, idx2 = mid, cnt = left;
        while (idx1 < mid && idx2 < right) {
            if (nums[indices[idx1]] > nums[indices[idx2]]) {
                buf[cnt] = indices[idx1];
                ans[indices[idx1++]] += (right - idx2);
            } else {
                buf[cnt] = indices[idx2++];
            }
            ++cnt;
        }
        while (idx1 < mid) buf[cnt++] = indices[idx1++];
        while (idx2 < right) buf[cnt++] = indices[idx2++];
        
        for (int i = left; i < right; i++) indices[i] = buf[i];
        
        return;
    }
    vector<int> countSmaller(vector<int>& nums) {
        indices.resize(nums.size());
        buf.resize(nums.size());
        ans.resize(nums.size());
        for (int i = 0; i < (int)ans.size(); i++) ans[i] = 0;
        
        for (int i = 0; i < (int)indices.size(); i++) indices[i] = i;
        mergesort(nums, 0, nums.size());
        
        return ans;
    }
};

//another mergeSort modify

C++ Accepted Code:

class Solution {
protected:
    void merge_countSmaller(vector<int>& indices, int first, int last, 
                            vector<int>& results, vector<int>& nums) {
        int count = last - first;
        if (count > 1) {
            int step = count / 2;
            int mid = first + step;
            merge_countSmaller(indices, first, mid, results, nums);
            merge_countSmaller(indices, mid, last, results, nums);
            vector<int> tmp;
            tmp.reserve(count);
            int idx1 = first;
            int idx2 = mid;
            int semicount = 0;
            while ((idx1 < mid) || (idx2 < last)) {
                if ((idx2 == last) || ((idx1 < mid) &&
                       (nums[indices[idx1]] <= nums[indices[idx2]]))) {
					tmp.push_back(indices[idx1]);
                    results[indices[idx1]] += semicount;
                    ++idx1;
                } else {
					tmp.push_back(indices[idx2]);
                    ++semicount;
                    ++idx2;
                }
            }
            move(tmp.begin(), tmp.end(), indices.begin()+first);
        }
    }
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> results(n, 0);
        vector<int> indices(n, 0);
        iota(indices.begin(), indices.end(), 0);
        merge_countSmaller(indices, 0, n, results, nums);
        return results;
    }
};

/*

Personally I don't think this is a good solution.
First of all the implementation shown has a worst case of O(n^2) because the tree can be skewed.
Second, it's non-trivial to build a self-balancing tree, even just for insertion.
I recommend the other solution that modifies merge-sort to accomplish the task. 
It's truly beautiful and guaranteed O(nlog(n)).

*/
// BST solution
class Solution {
public:
    
    class TreeNode {
        public:
        TreeNode *left, *right;
        int val, index, sum, freq;
        TreeNode (int val, int index) {
            this->val = val;
            this->index = index;
            this->sum = 0;
            this->freq = 1;
            this->left = this->right = nullptr;
        }
    };
    
    class BST {
        public:
        TreeNode *r;
        BST() {
            r = nullptr;
        }
        
        TreeNode *insert(TreeNode *root, int val, int index, vector <int>& count, int pre) {
            if (root == nullptr) {
                root = new TreeNode(val, index);
                if (!this->r) this->r = root;
                count[index] = pre;
                return root;
            }
            if (val == root->val) {
                root->freq++;
                count[index] = pre + root->sum;
            } else if (val < root->val) {
                root->sum++;
                root->left = insert(root->left, val, index, count, pre);
            } else {
                //count[index] += ((root->sum + 1)*root->freq);
                root->right = insert(root->right, val, index, count, pre + root->freq + root->sum);
            }
            return root;
        }
    };
    
    vector<int> countSmaller(vector<int>& nums) {
        if (nums.size() == 0) return nums;
        vector<int> count(nums.size(), 0);
        BST bst;
        for (int i = nums.size() - 1; i >= 0; --i)
            bst.insert(bst.r, nums[i], i, count, 0);
        return count;
    }
};

//lower_bound
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> result(nums.size(), 0);
        vector<int> temp;
        
        for(int i=nums.size()-1; i>=0; i--){
            int indx = lower_bound(temp.begin(), temp.end(), nums[i]) - temp.begin();
            temp.insert(temp.begin() + indx, nums[i]);
            result[i] = indx;
        }
        return result;
    }
};

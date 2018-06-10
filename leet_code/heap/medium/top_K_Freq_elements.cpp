/*

Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note: 
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.

*/

//Complexity
//O(n log(n-k)





//Using priority_queue

/*
C++ priority queue by default puts the highest prorirty element
at the top of the queue. ( means that the elements are sorted in descending
order).
*/
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        if(!nums.size()) return vector<int>();
        vector<int> res;
        unordered_map<int,int> table;
        for(int e :nums) {
        	++table[e];
        }
        priority_queue<pair<int,int>> heap;
        for(auto e : table) {
        	heap.push(make_pair(e.second,e.first));
        }
        for(int i=0;i<k;++i) {
        	res.push_back(heap.top().second);
        	heap.pop();
        }
        return res;
    }
};

//Using heap
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        if (nums.empty()) return {};
        unordered_map<int, int> m;
        for (auto &n : nums) m[n]++;
    
        vector<pair<int, int>> heap;
        for (auto &i : m) heap.push_back({i.second, i.first});
    
        vector<int> result; 
        make_heap(heap.begin(), heap.end());
        while (k--) {
            result.push_back(heap.front().second);
            pop_heap(heap.begin(), heap.end());
            heap.pop_back();
        }
        return result;
}
};




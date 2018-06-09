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
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> map;
        for(int num : nums){
            map[num]++;
        }

        vector<int> res;
        /** use the priority queue, like the max-heap , we will keep (size-k) smallest elements in the queue**/
        /** pair<first, second>: first is frequency,  second is number **/
        priority_queue<pair<int,int>> pq; 
        for(auto it = map.begin(); it != map.end(); it++){
            pq.push(make_pair(it->second, it->first));
            /** onece the size bigger than size-k, we will pop the value, which is the top k frequent element value **/
            if(pq.size() > (int)map.size() - k){
                res.push_back(pq.top().second);
                pq.pop();
            }
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




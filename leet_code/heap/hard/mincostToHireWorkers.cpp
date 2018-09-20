/*
There are N workers.  The i-th worker has a quality[i] and a minimum wage expectation wage[i].
Now we want to hire exactly K workers to form a paid group.  When hiring a group of K workers, 
we must pay them according to the following rules:
1. Every worker in the paid group should be paid in the ratio of their quality compared to other workers in the paid group.
2. Every worker in the paid group must be paid at least their minimum wage expectation.


Example 1:
Input: quality = [10,20,5], wage = [70,50,30], K = 2
Output: 105.00000
Explanation: We pay 70 to 0-th worker and 35 to 2-th worker.

Example 2:
Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], K = 3
Output: 30.66667
Explanation: We pay 4 to 0-th worker, 13.33333 to 2-th and 3-th workers seperately. 
*/

class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
        int N = quality.size();
        vector<pair<double, int>>vec; // ratio, quality
        for(int i = 0; i < N; i++) {
            vec.push_back(make_pair(wage[i] * 1.0 / quality[i], quality[i])); 
        }
				// sort in ascending order
        sort(vec.begin(), vec.end(), [](auto& a, auto& b){
            return a.first < b.first;
        });
        int quality_cnt = 0;
        priority_queue<int> q; // max-min heap
        for(int i = 0; i < K; i++) {
            quality_cnt += vec[i].second;
            q.push(vec[i].second);
        }
        double ans = quality_cnt * vec[K - 1].first;
        for(int i = K; i < N; i++) {
            q.push(vec[i].second);
            quality_cnt += vec[i].second;
            quality_cnt -= q.top();
            q.pop();
            ans = min(ans, quality_cnt * vec[i].first);
        }
        return ans;
    }
};

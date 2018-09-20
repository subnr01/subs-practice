/*


*/



//Solution 1

class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int M, int N) {
        if (N == 0) {
            return 0;
        }
        vector<vector<pair<int, int>>> graph(N);
        for (auto& edge : edges) {
            graph[edge[0]].push_back({edge[1], edge[2]});
            graph[edge[1]].push_back({edge[0], edge[2]});
        }
        vector<bool> visit(N, false);
        vector<int> step(N, -1);
        priority_queue<pair<int, int>> maxheap;
        maxheap.push({M, 0});
        while (!maxheap.empty()) {
            int remain = maxheap.top().first;
            int node = maxheap.top().second;
            maxheap.pop();
            if (visit[node]) {
                continue;
            }
            step[node] = remain;
            visit[node] = true;
            for (auto& path : graph[node]) {
                int next_node = path.first;
                int total_nodes = path.second;
                if (remain > total_nodes && !visit[next_node]) {
                    maxheap.push({remain - 1 - total_nodes, next_node});
                }
            }
        }
        int sum = 0;
        for (int node = 0; node < N; ++node) {
            if (visit[node]) {
                ++sum;
            }
        }
        for (auto& edge : edges) {
            int p1 = step[edge[0]] < 0 ? 0 : step[edge[0]];
            int p2 = step[edge[1]] < 0 ? 0 : step[edge[1]];
            sum += min(edge[2], p1 + p2);
        }
        return sum;
    }
};



//Slower soln (What is the difference between the two???)
class Solution {
public:
    int reachableNodes(vector<vector<int>> edges, int M, int N) {
        unordered_map<int, unordered_map<int, int>> e;
        for (auto v : edges) e[v[0]][v[1]] = e[v[1]][v[0]] = v[2];
        priority_queue<pair<int, int>> pq;
        pq.push({M, 0});
        unordered_map<int, int> seen;
        while (pq.size()) {
            int moves = pq.top().first, i = pq.top().second;
            pq.pop();
            if (!seen.count(i)) {
                seen[i] = moves;
                for (auto j : e[i]) {
                    int moves2 = moves - j.second - 1;
                    if (!seen.count(j.first) && moves2 >= 0)
                        pq.push({ moves2, j.first});
                }
            }
        }
        int res = seen.size();
        for (auto v : edges) {
            int a = seen.find(v[0]) == seen.end() ? 0 : seen[v[0]];
            int b = seen.find(v[1]) == seen.end() ? 0 : seen[v[1]];
            res += min(a + b, v[2]);
        }
        return res;
    }
};


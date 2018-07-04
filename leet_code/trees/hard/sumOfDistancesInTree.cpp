/*
An undirected, connected tree with N nodes labelled 0...N-1 and N-1 edges are given.

The ith edge connects nodes edges[i][0] and edges[i][1] together.

Return a list ans, where ans[i] is the sum of the distances between node i and all other nodes.

Example
Input: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation: 
Here is a diagram of the given tree:
  0
 / \
1   2
   /|\
  3 4 5
We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
equals 1 + 1 + 2 + 2 + 2 = 8.  Hence, answer[0] = 8, and so on.


*/


class Solution {
public:
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        vector<unordered_set<int>> tree(N);
        vector<int> res(N, 0);
        vector<int> count(N, 0);
        if (N == 1) return res;
        for (auto e : edges) {
            tree[e[0]].insert(e[1]);
            tree[e[1]].insert(e[0]);
        }
        unordered_set<int> seen1, seen2;
        dfs(0, seen1, tree, res, count);
        dfs2(0, seen2, tree, res, count, N);
        return res;

    }

    void dfs(int root, unordered_set<int>& seen, vector<unordered_set<int>>& tree, vector<int>& res, vector<int>& count) {
        seen.insert(root);
        for (auto i : tree[root])
            if (seen.count(i) == 0) {
                dfs(i, seen, tree, res, count);
                count[root] += count[i];
                res[root] += res[i] + count[i];
            }
        count[root] += 1;
    }

    void dfs2(int root, unordered_set<int>& seen, vector<unordered_set<int>>& tree, vector<int>& res, vector<int>& count, int N) {
        seen.insert(root);
        for (auto i : tree[root])
            if (seen.count(i) == 0) {
                res[i] = res[root] - count[i] + N - count[i];
                dfs2(i, seen, tree, res, count, N);
            };
    }
};

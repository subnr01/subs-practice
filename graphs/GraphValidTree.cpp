/*
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), check if these
edges form a valid tree.

Analysis

This problem can be converted to finding a cycle in a graph. It can be solved by using DFS (Recursion) or BFS (Queue).

*/

https://discuss.leetcode.com/topic/28436/simple-and-clean-c-solution-with-detailed-explanation/3

class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        if(edges.size() != n-1) return false;

        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        
        for(auto e : edges)
        {
            auto x = find(e.first), y = find(e.second);
            if(x == y) return false;
            parent[x] = y;
        }
        
        return true;
    }
private:
    vector<int> parent;
    int find(int x)
    {
        return parent[x] == x ? x : find(parent[x]);
    }
};

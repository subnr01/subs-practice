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
        vector<int> nodes(n,0);
        for(int i=0; i<n; i++) nodes[i] = i;
        for(int i=0; i<edges.size(); i++){
            int f = edges[i].first;
            int s = edges[i].second;
            while(nodes[f]!=f) f = nodes[f];
            while(nodes[s]!=s) s = nodes[s];
            if(nodes[f] == nodes[s]) return false;
            nodes[s] = f;
        }
        return edges.size() == n-1;
    }
};

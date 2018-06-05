/*
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), check if these
edges form a valid tree.

Analysis

This problem can be converted to finding a cycle in a graph. It can be solved by using DFS (Recursion) or BFS (Queue).


To tell whether a graph is a valid tree, we have to:

Make sure there is no cycle in the graph - this has to be a none-cyclic graph;
Make sure every node is reached - this has to be a connected graph;
*/

https://discuss.leetcode.com/topic/28436/simple-and-clean-c-solution-with-detailed-explanation/3


//Union find solution

class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        if(edges.size() != n-1) return false;

        parent.resize(n, -1);
        
        
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
        return parent[x] == -1 ? x : find(parent[x]);
    }
};


//DFS solution
class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        vector<vector<int>> neighbors(n);
        for (auto e : edges) {
            neighbors[e.first].push_back(e.second);
            neighbors[e.second].push_back(e.first);
        }
        vector<bool> visited(n, false);
        if (hasCycle(neighbors, 0, -1, visited))
            return false;
        for (bool v : visited)
            if (!v) {
                //Graph is disconnected. 
                // for example
                // [[0, 1], [2, 3]]
                // another very good example
                // [[2, 3] , [1, 2], [1, 3]]
                return false;
            }
        return true;
    } 
private:
    bool hasCycle(vector<vector<int>>& neighbors, int kid, int parent, vector<bool>& visited) {
        if (visited[kid]) return true;
        visited[kid] = true;
        for (auto neigh : neighbors[kid])
            if (neigh != parent && hasCycle(neighbors, neigh, kid, visited))
                return true;
        return false;
    }
};


/*
In this problem, a tree is an undirected graph that is connected and has no cycles.

The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N),
with one additional edge added. The added edge has two different vertices chosen from 1 to N, and was 
not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] with u < v, 
that represents an undirected edge connecting nodes u and v.

Return an edge that can be removed so that the resulting graph is a tree of N nodes. If there are 
multiple answers, return the answer that occurs last in the given 2D-array.
The answer edge [u, v] should be in the same format, with u < v.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given undirected graph will be like this:
  1
 / \
2 - 3
Example 2:
Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
Output: [1,4]
Explanation: The given undirected graph will be like this:
5 - 1 - 2
    |   |
    4 - 3
Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.


We have overhauled the problem description + test cases and specified clearly the graph is an undirected graph.
For the directed graph follow up please see Redundant Connection II). 
We apologize for any inconvenience caused.

*/


//Related topics:  Tree, Union Find, Graphs


//Union find soln ( what is this, path compression or union by rank soln, find out )
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> parent(1001, -1);
        
        
        for (auto e : edges)
        {
            auto x = find(parent, e[0]), y = find(parent, e[1]);
            if(x == y) return e;
            parent[x] = y;
        }
        return {0,0};
    }
    
    int find(vector<int> & parent, int x){
        return parent[x] == -1 ? x : find(parent, parent[x]);
    }
};


//DFS Soln: O(n^2), space complexity 0(n)
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        unordered_map<int, unordered_set<int>> m;
        for (auto edge : edges) {
            if (hasCycle(edge[0], edge[1], m, -1)) return edge;
            m[edge[0]].insert(edge[1]);
            m[edge[1]].insert(edge[0]);
        }
        return {};
    }
    bool hasCycle(int cur, int target, unordered_map<int, unordered_set<int>>& m, int parent) {
        if (m[cur].count(target)) {
          /*
          target is already connected to cur.
          so this must be a loop.
          */
          return true;
        }
        for (int neigh : m[cur]) {
            if (neigh == parent) {
              /* 
              if neigh is same as the parent
              then continue
              */
      
              continue;
            }
            if (hasCycle(neigh, target, m, cur)) {
              /*
              If neigh and the target are connected, then
              there is a cycle, as cur and target were assumed
              to be connected, when we entered this function
              */
              return true;
            }
        }
        return false;
    }
};

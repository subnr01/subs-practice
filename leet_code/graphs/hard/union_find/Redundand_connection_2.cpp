/*

In this problem, a rooted tree is a directed graph such that, there is exactly one node 
(the root) for which all other nodes are descendants of this node, plus every node has 
exactly one parent, except for the root node which has no parents.

The given input is a directed graph that started as a rooted tree with N nodes (with distinct
values 1, 2, ..., N), with one additional directed edge added. The added edge has two different 
vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] 
that represents a directed edge connecting nodes u and v, where u is a parent of child v.

Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes. 
If there are multiple answers, return the answer that occurs last in the given 2D-array.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given directed graph will be like this:
  1
 / \
v   v
2-->3
Example 2:
Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
Output: [4,1]
Explanation: The given directed graph will be like this:
5 <- 1 -> 2
     ^    |
     |    v
     4 <- 3
     
     
Another very good example:-
Input:
[[2,1],[3,1],[4,2],[1,4]]

Output:
[2,1]
*/


//Related topics: DFS, Union Find, graph
class Solution {
private:
    int findparent(vector<int>& parents, int u)
    {
        if (u != parents[u])
        {
            parents[u] = findparent(parents, parents[u]);
        }
        
        return parents[u];
    }
    
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int N = edges.size();
        if (N == 0)
        {
            return vector<int>();
        }
        
        vector<int> parents(N + 1, 0), edgeA, edgeB;
            
        // find if we have one node has two parents
        for (auto& edge : edges)
        {
            int u = edge[0], v = edge[1];
            if (parents[v] == 0)
            {
                parents[v] = u;
            }
            else
            {
                edgeA = {parents[v], v};
                edgeB = edge;
                
                // set edge to a dummy node so it won't break cycle check
                edge[1] = 0;
            }
        }
        
        for (int i = 1; i <= N; i++)
        {
            parents[i] = i;
        }
        
        // detect circle
        for(auto& edge : edges)
        {
            int u = edge[0], v = edge[1], pu = findparent(parents, u);
            if (pu == v)
            {
                return edgeA.empty() ? edge : edgeA;
            }
            
            parents[v] = pu;
        }
        
        return edgeB;
    }
};


// DFS Solution
// Need to find the DFS Solution. 
// There is a DFS solution given as a standard solution.
// need to convert that???

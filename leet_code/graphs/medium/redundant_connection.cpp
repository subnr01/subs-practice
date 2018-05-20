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
        vector<int> parent(1001, 0);
        for (int i = 1; i!=parent.size();++i){
            parent[i] = i;
        }
        for (auto e : edges){
            if (unionFind(parent, e[0]) == unionFind(parent, e[1])) return e;
            parent[unionFind(parent,e[1])] = unionFind(parent,e[0]);
        }
        return {0,0};
    }
    
    int unionFind(vector<int> & p, int t){
        if (t!=p[t])
            p[t] = unionFind(p,p[t]);
        return p[t];
    }
};


//DFS Soln: O(n^2), space complexity 0(n)
class Solution {
    Set<Integer> seen = new HashSet();
    int MAX_EDGE_VAL = 1000;

    public int[] findRedundantConnection(int[][] edges) {
        ArrayList<Integer>[] graph = new ArrayList[MAX_EDGE_VAL + 1];
        for (int i = 0; i <= MAX_EDGE_VAL; i++) {
            graph[i] = new ArrayList();
        }

        for (int[] edge: edges) {
            seen.clear();
            if (!graph[edge[0]].isEmpty() && !graph[edge[1]].isEmpty() &&
                    dfs(graph, edge[0], edge[1])) {
                return edge;
            }
            graph[edge[0]].add(edge[1]);
            graph[edge[1]].add(edge[0]);
        }
        throw new AssertionError();
    }
    public boolean dfs(ArrayList<Integer>[] graph, int source, int target) {
        if (!seen.contains(source)) {
            seen.add(source);
            if (source == target) return true;
            for (int nei: graph[source]) {
                if (dfs(graph, nei, target)) return true;
            }
        }
        return false;
    }
}


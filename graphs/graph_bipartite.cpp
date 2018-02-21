/*
Given a graph, return true if and only if it is bipartite.

Recall that a graph is bipartite if we can split it's set of nodes into two independent subsets A and B such that every edge in 
the graph has one node in A and another node in B.

The graph is given in the following form: graph[i] is a list of indexes j for which the edge between nodes i and j exists.  
Each node is an integer between 0 and graph.length - 1.  There are no self edges or parallel edges: graph[i] does not contain i, 
and it doesn't contain any element twice.

Example 1:
Input: [[1,3], [0,2], [1,3], [0,2]]
Output: true
Explanation: 
The graph looks like this:
0----1
|    |
|    |
3----2
We can divide the vertices into two groups: {0, 2} and {1, 3}.
Example 2:
Input: [[1,2,3], [0,2], [0,1,3], [0,2]]
Output: false
Explanation: 
The graph looks like this:
0----1
| \  |
|  \ |
3----2
We cannot find a way to divide the set of nodes into two independent ubsets.

*/


https://leetcode.com/articles/is-graph-bipartite/


//BFS approach
bool isBipartite(vector<vector<int>>& graph) {
    // vector subset indicates the subset node is in: 0 for unvisited, 1 for set A, -1 for set B
    vector<int> subset(graph.size(), 0);

    for (int i = 0; i < graph.size(); i++) {
        // if not in any subset (start of new disjoint graph), arbitrarily put in set A (set 1)
        if (subset[i] == 0)
            subset[i] = 1;
        // DFS queue to sort all connected edges
        queue<int> connections;
        connections.push(i);

        while (!connections.empty()) {
            int node = connections.front();
            connections.pop();
            for (int j = 0; j < graph[node].size(); j++) {
                // every edge connects to otherNode, which can be in...
                int otherNode = graph[node][j];
                // same subset: violates bipartite
                if (subset[otherNode] == subset[node])
                    return false;
                // no subset: put into subset that node is not in
                if (subset[otherNode] == 0) {
                    subset[otherNode] = -subset[node];
                    connections.push(otherNode);
                }
                // otherwise, already in different subset, continue;
            }
        }
    }
    // if every connection passes, graph is bipartite
    return true;
}

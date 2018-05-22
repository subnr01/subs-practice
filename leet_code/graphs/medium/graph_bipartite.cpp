/*
Given a graph, return true if and only if it is bipartite.

Recall that a graph is bipartite if we can split it's set of nodes into two independent subsets A and B such that 
every edge in the graph has one node in A and another node in B.

The graph is given in the following form: graph[i] is a list of indexes j for which the edge between nodes i and j exists.  
Each node is an integer between 0 and graph.length - 1.  There are no self edges or parallel edges: graph[i] does
not contain i, and it doesn't contain any element twice.

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

//the Soln also contains DFS, is DFS preferred
//DFS approach


//Logic
// Every neighbor gets colored the opposite color from the current node. 
// If we find a neighbor colored the same color as the current node, 
// then our coloring was impossible.
// if x is colored 1, then its neighbors must be colored -1. 
// if we find two neighbors having the same color, then return false
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
                    // neighbor has the same color, 
                    // maybe -1.
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

//BFS approach
class Solution {
public:
    // BFS coloring (can also use DFS using stack)
    bool colorComponent(int node, auto& graph, auto& colors){    
        queue<int> q;    
        q.push(node);
            
        while(!q.empty()){
            int current = q.front(); q.pop();
            
            vector<int> neighbours = graph[current];
            
            // for each neighbour, if colored verify that it's not the same as current node color
            // else color it with the other color. 
            for(int neighbour : neighbours){
                if(colors[neighbour] == -1){
                    colors[neighbour] = (1 - colors[current]);
                    q.push(neighbour);
                }
                else{
                    if(colors[neighbour] == colors[current]) return false;
                }
                
            }    
        }
        
        return true;
    }
    
    // bipartite = 2 coloring problem of graph
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> colors(graph.size(), -1);   // 0 - red, 1 - blue , -1 - uncolored
        
        for(int i = 0; i < graph.size(); i++){
            
            // find a component that is uncolored
            if(colors[i] == -1 && graph[i].size() > 0){
            
                // color starting vertex as red, and proceed to color neighbours with blue and red alternatively if possible
                colors[i] = 0;
                bool possible = colorComponent(i, graph, colors);
                
                if(!possible) return false;
            }
        }
        
        return true;
    }
};

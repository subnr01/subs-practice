/*
In a directed graph, we start at some node and every turn, walk along a directed edge of the graph.  
If we reach a node that is terminal (that is, it has no outgoing directed edges), we stop.

Now, say our starting node is eventually safe if and only if we must eventually walk to a terminal node.  
More specifically, there exists a natural number K so that for any choice of where to walk, we must have stopped
at a terminal node in less than K steps.

Which nodes are eventually safe?  Return them as an array in sorted order.

The directed graph has N nodes with labels 0, 1, ..., N-1, where N is the length of graph.  
The graph is given in the following form: graph[i] is a list of labels j such that (i, j) is a directed edge of the graph.

Example:
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Here is a diagram of the above graph.

*/



//147ms
class Solution {
public:
    bool isSafe(int i, const vector<vector<int>> &graph, vector<int> &color) {
        if(color[i] != 0) {
            if(color[i] == 1) 
                return false;
            else 
                return true;
        }
        color[i] = 1;
        for(const int ele : graph[i]) {
            if(!isSafe(ele, graph, color)) {
                return false;
            }
        }
        color[i] = 2;
        return true;
    }
    
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        vector<int> res;
        int nodeCount = graph.size();
        vector<int> color(nodeCount, 0);
        for(int i = 0; i < nodeCount; ++i) {
            if(isSafe(i, graph, color)) {
                res.push_back(i);
            }
        }
        
        
        
        return res;
    }
};


//146ms
class Solution {
public:
   bool dfs(vector<vector<int>>& graph, vector<int> &dp, int src) {
   if(dp[src])
       return 1 == dp[src];

    dp[src] = -1;
    for(auto node : graph[src])
        if(false == dfs(graph, dp, node))
            return false;
    return dp[src] = 1;
}
vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    int total_nodes = graph.size();
    vector<int> result, dp(total_nodes, 0);
    for(int i = 0; i < total_nodes; i++)
        if(dfs(graph, dp, i))
            result.push_back(i);
    
    return result;
}  
};



//174ms ms
#define GRAY 1
#define WHITE 0
#define BLACK 2
class Solution {
public:
    vector<int> vis;
    vector<vector<int>> g;
    vector<int> f;
    int n;
    void dfs(int u) {
        vis[u] = GRAY;
        f[u] = 1;
        for (int v : g[u]) {
            if (vis[v] == GRAY)
                f[u] = 0;
            else {
                if (vis[v] == WHITE)
                    dfs(v);
                f[u] &= f[v];
            }
        }
        vis[u] = BLACK;
    }
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        g = graph;
        n = graph.size();
        f = vector<int>(n, -1);
        vis = vector<int>(n, WHITE);
        for (int i = 0; i < n; i++) {
            if (vis[i] == WHITE)
                dfs(i);
        }
        vector<int> ans;
        for (int i = 0; i < n; i++)
            if (f[i] == 1)
                ans.push_back(i);
        return ans;
    }
};

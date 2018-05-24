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


//this is based on the famous grey, white, black of dfs
//147ms
class Solution {
public:
    bool isSafe(int i, const vector<vector<int>> &graph, vector<int> &color) {
        if(color[i] > 0) {
            return color[i] == 2;
        }
        color[i] = 1;
        for(const int ele : graph[i]) {
            
            if (!isSafe(ele, graph, color)) {
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


//There is also the reverse edge soln article. take a look



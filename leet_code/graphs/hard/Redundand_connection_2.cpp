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
     
     
*/


//Related topics: DFS, Union Find, graph
//look at https://leetcode.com/problems/redundant-connection-ii/discuss/108073/share-my-solution-c
// 7ms
class Solution {
public:
    int root(vector<int>& parent, int num){
        while(parent[num] != num){
            num = parent[num];
        }
        return num;
    }
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        vector<int> ret;
        if(edges.size() == 0) return ret;
        vector<int> parent(edges.size() + 1, 0);
        vector<int> canA(0);
        vector<int> canB(0);
        for(auto it = edges.begin(); it != edges.end(); it++){
            if(parent[(*it)[1]] != 0){
                canA = {parent[(*it)[1]], (*it)[1]};
                canB = (*it);
                edges.erase(it);
                break;
            }
            parent[(*it)[1]] = (*it)[0];
        }
        
        for(int i = 1; i < parent.size(); i++){
            parent[i] = i;
        }
        for(auto edge : edges){
            if(root(parent, edge[0]) == root(parent, edge[1])){
                if(canA.size() != 0) return canA;
                return edge;
            }
            parent[edge[1]] = edge[0];
        }
        return canB;
    }
    
    

};
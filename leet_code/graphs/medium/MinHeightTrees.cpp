/*
For a undirected graph with tree characteristics, we can choose any node as the root. The result graph 
is then a rooted tree. Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs).
Given such a graph, write a function to find all the MHTs and return a list of their root labels.

Format
The graph contains n nodes which are labeled from 0 to n - 1. You will be given the number n and a list
of undirected edges (each edge is a pair of labels).

You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the
same as [1, 0] and thus will not appear together in edges.

Example 1:

Given n = 4, edges = [[1, 0], [1, 2], [1, 3]]

        0
        |
        1
       / \
      2   3
return [1]

Example 2:

Given n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

     0  1  2
      \ | /
        3
        |
        4
        |
        5
return [3, 4]

*/


/*

https://leetcode.com/problems/minimum-height-trees/discuss/76055/Share-some-thoughts

Our problem want us to find the minimum height trees and return their root labels. First we can think 
about a simple case -- a path graph.

For a path graph of n nodes, find the minimum height trees is trivial. Just designate the middle point(s) as roots.

Despite its triviality, let design a algorithm to find them.

Suppose we don't know n, nor do we have random access of the nodes. We have to traversal. It is 
very easy to get the idea of two pointers. One from each end and move at the same speed. 
When they meet or they are one step away, (depends on the parity of n), we have the roots we want.

This gives us a lot of useful ideas to crack our real problem.

For a tree we can do some thing similar. We start from every end, by end we mean vertex of degree 1 (aka leaves). 
We let the pointers move the same speed. When two pointers meet, we keep only one of them, until the last two pointers meet 
or one step away we then find the roots.

It is easy to see that the last two pointers are from the two ends of the longest path in the graph.

The actual implementation is similar to the BFS topological sort. Remove the leaves, update the 
degrees of inner vertexes. Then remove the new leaves. Doing so level by level until 
there are 2 or 1 nodes left. What's left is our answer!

The time complexity and space complexity are both O(n).

Note that for a tree we always have V = n, E = n-1.
*/


// So the basic idea, is to first remove all the leaves (degree = 1) and then 
// update the existing vertices and obtain the new leaves and then perform the 
// same action again, until we 
// are left with two vertices. These vertices are the MHTS of the graph
//35 ms
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        vector<vector<int>> adj_list(n);
        vector<int> counter(n, 0);
        for (auto &p:edges){
            adj_list[p.first].push_back(p.second);
            adj_list[p.second].push_back(p.first);
            counter[p.first]++;
            counter[p.second]++;
        }
        queue<int> res;
        for (int i = 0; i < n; i++){
            if (counter[i] <= 1){
                res.push(i);
            }
        }
        while (n > 2){
            int leafsize = res.size();
            n -= leafsize;
            for (int i = 0; i < leafsize; i++){
                int node = res.front();
                res.pop();
                for (auto adj : adj_list[node]){
                    if (--counter[adj] == 1) res.push(adj);
                }
            }
        }
        vector<int> r;
        while (!res.empty()){
            r.push_back(res.front());
            res.pop();
        }
        return r;
    }
};


//66 ms
/*
https://discuss.leetcode.com/topic/30535/c-solution-o-n-time-o-n-space

The basic idea is "keep deleting leaves layer-by-layer, until reach the root."

Specifically, first find all the leaves, then remove them. After removing, some nodes will
become new leaves. So we can continue remove them. Eventually, there is only 1 or 2 nodes left. 
If there is only one node left, it is the root. If there are 2 nodes, either of them could be a possible root.

Time Complexity: Since each node will be removed at most once, the complexity is O(n).

Thanks for pointing out any mistakes.

Updates:
More precisely, if the number of nodes is V, and the number of edges is E. The space complexity 
is O(V+2E), for storing the whole tree. The time complexity is O(E), because we gradually 
remove all the neighboring information. As some friends pointing out, for a tree, if V=n, then E=n-1. 
Thus both time complexity and space complexity become O(n).

*/
class Solution {
    public:
        
        struct Node
        {
            unordered_set<int> neighbor;
            bool isLeaf()const{return neighbor.size()==1;}
        };
        
        vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
            
            vector<int> buffer1;
            vector<int> buffer2;
            vector<int>* pB1 = &buffer1;
            vector<int>* pB2 = &buffer2;
            if(n==1)
            {
                buffer1.push_back(0);
                return buffer1;
            }
            if(n==2)
            {
                buffer1.push_back(0);
                buffer1.push_back(1);
                return buffer1;
            }
            
            // build the graph
            vector<Node> nodes(n);
            for(auto p:edges)
            {
                nodes[p.first].neighbor.insert(p.second);
                nodes[p.second].neighbor.insert(p.first);
            }
            
            // find all leaves
            for(int i=0; i<n; ++i)
            {
                if(nodes[i].isLeaf()) pB1->push_back(i);
            }

            // remove leaves layer-by-layer            
            while(1)
            {
                for(int i : *pB1)
                {
                    for(auto n: nodes[i].neighbor)
                    {
                        nodes[n].neighbor.erase(i);
                        if(nodes[n].isLeaf()) pB2->push_back(n);
                    }
                }
                if(pB2->empty())
                {
                    return *pB1;
                }
                pB1->clear();
                swap(pB1, pB2);
            }
            
        }
    };

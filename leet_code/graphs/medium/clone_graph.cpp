/*
Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.


OJ's undirected graph serialization:
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/


*/


/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */

//Does a DFS, but puts everything back to every level, and when it comes
//back to the original call, it puts the neigbours for that particular node

// 1 -> 2, 3 
// 2 -> 4
// 3 -> 1
// 4 -> 2
// recursively take 2 neighbor of 1, setup 2 and its neighbors and then return 2 back to 1 
// so that it becomes neighbor of 1 and continue with 3.

/*
LOGIC:
We perform a DFS here.

We take a hash table that has a node as the key and its clone as the value.
The function will be called recursively like in any DFS function.
In the function, we try to find whether the input node is already part of
the hash, if node we create a new node and assign the node value to the
hash with input node as key. Now we got a clone node, but we still have
to initliase its neighbors. 

So we take a loop and get the neighbors of the input node one by one
and and invoke the clone function on each of the neighbors and 
obtain the returned cloned nodes of the neighbors and push
it into the vector of neighbors of the orignial clone node one by one.
This is DFS because, we call the function recursively on each neighbor which
inturn recursviely calls the function on the neighbors of the niebors.
*/

class Solution {
public:
    unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> hash;
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
       if (!node) return node;
       if(hash.find(node) == hash.end()) {
           hash[node] = new UndirectedGraphNode(node -> label);
           for (auto x : node -> neighbors) {
                (hash[node] -> neighbors).push_back( cloneGraph(x) );
           }
       }
       return hash[node];
    }
};

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


//Union find
class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> parent(n+1, 0), candA, candB;
        // step 1, check whether there is a node with two parents
        for (auto &edge:edges) {
            if (parent[edge[1]] == 0)
                parent[edge[1]] = edge[0]; 
            else {
                candA = {parent[edge[1]], edge[1]};
                candB = edge;
                edge[1] = 0;
            }
        } 
        // step 2, union find
        for (int i = 1; i <= n; i++) parent[i] = i;
        for (auto &edge:edges) {
            if (edge[1] == 0) continue;
            int u = edge[0], v = edge[1], pu = root(parent, u);
            // Now every node only has 1 parent, so root of v is implicitly v
            if (pu == v) {
                if (candA.empty()) return edge;
                return candA;
            }
            parent[v] = pu;
        }
        return candB;
    }
private:
    int root(vector<int>& parent, int k) {
        if (parent[k] != k) 
            parent[k] = root(parent, parent[k]);
        return parent[k];
    }
};


//very fast Union find soln
class UnionFind {
public:
	vector<int> Size, P;
	UnionFind(int N) {
		Size = vector<int>(N + 1, 1);
		P.resize(N + 1);
		for (int i = 1; i <= N; i++)P[i] = i;
	}
	int Find(int x) {
		if (P[x] == x) return x;
		return P[x] = Find(P[x]);
	}
	bool Union(int x, int y) { // return 1 if it is a cycle creator
		int Ux = Find(x), Uy = Find(y);
		if (Ux == Uy)return 1;
		if (Size[Ux] < Size[Uy])swap(Ux, Uy);
		Size[Ux] += Size[Uy];
		P[Uy] = Ux;
		return 0;
	}
};
class Solution {
public:
	vector<int> findRedundantDirectedConnection(vector<vector<int>>&Edge) {
		int N = Edge.size();
		vector<int>ans1, ans2, Parent(N+1,0);
		for (auto &e : Edge) 
			if (Parent[e[1]]){
				ans1 = { Parent[e[1]], e[1] };
				ans2 = e;
			}
			else Parent[e[1]] = e[0];
		// Cycle Check
		UnionFind UF(N);
		for (auto &e : Edge) {
			if (e == ans2)continue; // Cutoff ans2
			if (UF.Union(e[0], e[1]))
				return (ans1.empty()) ? e : ans1;
		}
		return ans2;
	}
};

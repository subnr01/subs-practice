/*

Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to 
find the number of connected components in an undirected graph.
Example 1:
     0          3
     |          |
     1 --- 2    4
Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], return 2.
Example 2:
     0           4
     |           |
     1 --- 2 --- 3
Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]], return 1.
Note:
You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.
*/


//https://discuss.leetcode.com/topic/32677/short-union-find-in-python-ruby-c/8



C++ solution 1
//10 ms     
     
/*
Union find example
(lldb) p leader
(std::__1::vector<int, std::__1::allocator<int> >) $0 = size=4 {
  [0] = 1
  [1] = 2
  [2] = 3
  [3] = -1
}

for input
vector<pair<int, int>> edges ={{0,1}, {1,2}, {2,3}, {3,0}};
*/
class Solution {
public:
    vector<int> leader;
    
    int getParent(int child) {
        return leader[child] == -1 ? child: getParent(leader[child]);
    }
    
    int countComponents(int n, vector<pair<int, int>>& edges) {
        leader.resize(n, -1);
        for (auto& pr : edges) {
            int x = getParent(pr.first);
            int y = getParent(pr.second);
            if (x != y) {
                leader[x] = y;  
            }
        }
        
        int rv = 0;
        for (int i = 0; i < n; i++) {
            if (leader[i] == -1) {
                rv++;
            }
        }
            
        return rv;
    }
};

C++ solution 2
//17 ms
class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        vector<int> id(n);
        iota(begin(id), end(id), 0);
        int count = n;
        
        for (auto e : edges) {
            int i = e.first;
            int j = e.second;
            while (i != id[i]) {
                i = id[i];
            }
            while (j != id[j]) {
                j = id[j];
            }
            if (i != j) {
                id[j] = i;
                count--;
            }
        }
        return count;
    }
};

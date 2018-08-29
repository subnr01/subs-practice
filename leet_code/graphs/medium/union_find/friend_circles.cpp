/*
There are N students in a class. Some of them are friends, while some are not. 
Their friendship is transitive in nature. For example, if A is a direct friend of B, 
and B is a direct friend of C, then A is an indirect friend of C. And we defined a friend 
circle is a group of students who are direct or indirect friends.

Given a N*N matrix M representing the friend relationship between students in the class. If M[i][j] = 1, 
then the ith and jth students are direct friends with each other, otherwise not. And you have to 
output the total number of friend circles among all the students.

Example 1:
Input: 
[[1,1,0],
 [1,1,0],
 [0,0,1]]
Output: 2
Explanation:The 0th and 1st students are direct friends, so they are in a friend circle. 
The 2nd student himself is in a friend circle. So return 2.
Example 2:
Input: 
[[1,1,0],
 [1,1,1],
 [0,1,1]]
Output: 1
Explanation:The 0th and 1st students are direct friends, the 1st and 2nd students are direct friends, 
so the 0th and 2nd students are indirect friends. All of them are in the same friend circle, so return 1.

*/


class Solution {
public:
    // Quick union
    int findCircleNum(vector<vector<int>>& M) {
        for (int i = 0; i < M.size(); ++i) parent.push_back(i);
        cout<<M.size()<<endl;
        int count = M.size();
        
        for (int i = 0; i < M.size(); ++i) {
            for (int j = i + 1; j < M.size(); ++j) {
                if (M[i][j] != 0 && root(i) != root(j)) {
                    parent[root(j)] = root(i); // merge j's group into i's group
                    --count; // now we have one fewer group
                }
            }
        }
        return count;
    }
    
    int root(int i) {
        while (parent[i] != i) i = parent[i];
        return i;
    }
    
    vector<int> parent;
};


//DFS Soln (slower)
class Solution {
public:
	void DFS(int x, vector<vector<int>>& A, vector<bool>& Vis) {
		Vis[x] = 1;
		for (int y = 0; y < A.size(); y++) {
			if (A[x][y] && !Vis[y]) DFS(y, A, Vis);
		}
	}
	int findCircleNum(vector<vector<int>>& A) {
		int GroupN = 0;
		vector<bool>Vis(A.size(), 0);

		for (int i = 0; i < A.size(); i++) {
			if (!Vis[i]) {
				GroupN++;
				DFS(i, A, Vis);
			}
		}
		return GroupN;
	}
};

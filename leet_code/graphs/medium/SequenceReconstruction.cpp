/*

THIS IS A TOPOLOGICAL SORT PROBLEM 
Check whether the original sequence org can be uniquely reconstructed from the sequences in seqs. 
The org sequence is a permutation of the integers from 1 to n, with 1 ≤ n ≤ 104. Reconstruction 
means building a shortest common supersequence of the sequences in seqs (i.e., a shortest sequence
so that all sequences in seqs are subsequences of it). Determine whether there is only one sequence
that can be reconstructed from seqs and it is the org sequence.

Example 1:

Input:
org: [1,2,3], seqs: [[1,2],[1,3]]

Output:
false

Explanation:
[1,2,3] is not the only one sequence that can be reconstructed, because [1,3,2] is also a valid sequence 
that can be reconstructed.
Example 2:

Input:
org: [1,2,3], seqs: [[1,2]]

Output:
false

Explanation:
The reconstructed sequence can only be [1,2].
Example 3:

Input:
org: [1,2,3], seqs: [[1,2],[1,3],[2,3]]

Output:
true

Explanation:
The sequences [1,2], [1,3], and [2,3] can uniquely reconstruct the original sequence [1,2,3].
Example 4:

Input:
org: [4,1,5,2,6,3], seqs: [[5,2,6,3],[4,1,5,2]]

Output:
true

*/


https://discuss.leetcode.com/topic/65961/simple-solution-one-pass-using-only-array-c-92ms-java-16ms
//68 ms
class Solution {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        int n = org.size();
        if(seqs.size() == 0) return false;
        if(n == 1){
            bool result = false;
            for(auto x : seqs){
                if(x.size() == 0) continue;
                if(x == org) result = true;
                else result = false;
            }
            return result;
        }
        vector<int> pos(n + 1, 0);
        for(int i = 0; i < n; i++) pos[org[i]] = i;
        vector<bool> flags(n + 1, false);
        int toMatch = n - 1;
        
        for(auto v : seqs){
            for(int i = 0; i < v.size(); i++){
                if(v[i] <= 0 || v[i] > n) return false;
                if(i == 0) continue;
                int x = v[i - 1];
                int y = v[i];
                if(pos[x] > pos[y]) return false;
                if(pos[x] + 1 == pos[y] && flags[x] == false){
                    flags[x] = true;
                    --toMatch;
                }
            }
        }
        return toMatch == 0;
    }

};
//64 ms
class Solution {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        if (seqs.empty()) {
            return false;
        }
        
        int n = org.size(), cnt = n - 1;
        vector<int> pos(n + 1, 0), flags(n + 1, 0);
        bool existed = false;
        for (int i = 0; i < n; ++i) {
            pos[org[i]] = i;
        }
        
        for (auto& seq : seqs) {
            for (int i = 0; i < seq.size(); ++i) {
                existed = true;
                if (seq[i] <= 0 || seq[i] > n) {
                    return false;
                }
                if (i == 0) {
                    continue;
                }
                
                int pre = seq[i - 1], cur = seq[i];
                if (pos[pre] >= pos[cur]) {
                    return false;
                }
                
                // set the flag if they are the consequence pair
                if (flags[cur] == 0 && pos[pre] + 1 == pos[cur]) {
                    flags[cur] = 1; 
                    --cnt;
                }
            }
        }
        return cnt == 0 && existed;
    }
};


//87ms
class Solution {
public:
  bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
    if (seqs.empty()) return false;

    vector<int> pos(org.size() + 1);
    for (int i = 0; i < org.size(); ++i)
      pos[org[i]] = i;

    unordered_set<int> visited;
    bool hasElement = false;
    int match = 0;
    
    for (const auto& v: seqs) {
      for (int i = 0; i < v.size(); ++i) {
	hasElement = true; // To handle case when org = [1], seqs = [[],[]]
	if (v[i] <= 0 || v[i] > org.size())
	  return false;

	if (i == 0) continue;
	int x = v[i - 1], y = v[i];
	if (pos[x] >= pos[y]) return false; // To handle case when org = [1], seqs = [[1,1]]
	if (visited.find(x) == visited.end() && pos[x] == pos[y] - 1) { // flag[x] means x position adjent element found or not
	  visited.insert(x); // Mark adjcent at postion x found
	  match++;
	}
      }
    }
    return match == org.size() - 1 && hasElement;
  }
};


//Another soln
// 147 ms
class Solution {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        int n = org.size();
        unordered_map<int, unordered_set<int>>graph;
        vector<int>indegree(n + 1, -1);
        for(auto v: seqs)
            for(int i = 0; i < v.size(); i++){
                if(v[i] > n || v[i] < 0) return false;
                if(indegree[v[i]] == -1) indegree[v[i]] = 0;
                if(i + 1 < v.size() && graph[v[i]].insert(v[i + 1]).second)
                    if(v[i + 1] > n || v[i + 1] < 0) return false;
                    else indegree[v[i + 1]] += indegree[v[i + 1]] < 0 ? 2 : 1;
            }
        for(int i = 0; i < n - 1; i++)
            if(indegree[org[i]] || !indegree[org[i + 1]]) return false;
            else for(auto x: graph[org[i]]) indegree[x]--;
        return indegree[org.back()] == 0;
    }
};

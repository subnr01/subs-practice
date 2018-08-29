/*

Two strings X and Y are similar if we can swap two letters (in different positions) of X, so that it equals Y.

For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar,
but "star" is not similar to "tars", "rats", or "arts".

Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.  Notice that 
"tars" and "arts" are in the same group even though they are not similar.  Formally, each group is such that a word is in the group if and only if it is similar to at least one other word in the group.

We are given a list A of unique strings.  Every string in A is an anagram of every other string in A.  
How many groups are there?

Example 1:

Input: ["tars","rats","arts","star"]
Output: 2

*/

//Related topics: DFS, Union Find, graphs


//243 ms
class Solution {
    struct disjoint_set {
    vector<int> v;
    int sz;
public:
    disjoint_set(int n) {
        makeset(n);
    }

    void makeset(int n) {
        v.resize(n);
        iota(v.begin(), v.end(), 0);
        sz = n;
    }

    int find(int i) {
        if (i != v[i])
            v[i] = find(v[i]);
        return v[i];
    }
    
    void join(int i, int j) {
        int ri = find(i), rj = find(j);
        if (ri != rj) {
            v[ri] = rj;
            sz--;
        }
    }
    
    int size() {
        return sz;
    }
};
public:
    bool similar(string &a, string &b) {
    int n = 0;
    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i] && ++n > 2)
            return false;
    return true;
}

int numSimilarGroups(vector<string>& A) {
    disjoint_set ds(A.size());
    for (int i = 0; i < A.size(); i++)
        for (int j = i + 1; j < A.size(); j++)
            if (similar(A[i], A[j]))
                ds.join(i, j);
    return ds.size();
}
};


//Union find soln 112 ms
class Solution {
public:
     int numSimilarGroups(vector<string>& A) {
      if(A.empty()) return 0;
      if(A[0].size()<20) return help2(A);
         else return help1(A);
    }
	bool check(string& str1, string& str2) {
		int len = str1.size(), cnt = 0;
		for (int i = 0; i < len; ++i) {
			if (str1[i] != str2[i]) {
				cnt++;
				if (cnt > 2)
					return false;
			}
		}
		return true;
	}
	int find(int x,vector<int>& p) {
		if (x != p[x]) p[x] = find(p[x],p);
		return p[x];
	}
    int help1(vector<string>& A) {
        int n = A.size();
        vector<int> fa(n, 0);
        for (int i = 0; i < n; ++i) {
            fa[i] = i;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (check(A[i],A[j])) {
					fa[find(i,fa)]=find(j,fa);
                }
            }
        }
        int ans=0;
     for(int i=0;i<fa.size();i++){
         if(fa[i]==i)
             ans++;
     }
        return ans;
    }
    int help2(vector<string>& A) {
		unordered_set<string> sA(A.begin(), A.end());
		queue<string> q;
		int n = 0;
		while (!sA.empty()) {
			q.push(*(sA.begin()));
			sA.erase(sA.begin());
			n++;
			while (!q.empty()) {
				string s = q.front();
				q.pop();
				for (int i = 0; i < s.size(); i++)
					for (int j = i + 1; j < s.size(); j++) {
						if (s[i] != s[j]) {
							swap(s[i], s[j]);
							if (sA.count(s)) {
								q.push(s);
								sA.erase(s);
							}
							swap(s[i], s[j]);
							if (sA.empty()) return n;
						}
					}
			}
		}
		return n;
	}
};

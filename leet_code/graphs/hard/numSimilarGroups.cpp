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


//Union find soln 670 ms
class Solution {
public:
    int numSimilarGroups(vector<string>& A) {
        unordered_map<string,string> mapping;
        int n = A.size();
        for (int i = 0; i < n; i++) {
            mapping[A[i]] = A[i];
            for (int j = 0; j < i; j++) {
                if (isSimilar(A[i], A[j]) && mapping[A[j]] != A[i]) {
                    string x = getRoot(A[j], mapping);
                    mapping[x] = A[i];
                }
            }
        }
        
        int result = 0;
        for (auto it = mapping.begin(); it != mapping.end(); it++) {
            if (it->first == it->second) result++;
        }
        return result;
    }
    
private:
    bool isSimilar(string &a, string &b) {
        int n = a.length(), counter = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] != b[i]) counter++;
        }
        return counter == 2;
    }
    
    string getRoot(string s, unordered_map<string,string> &mapping) {
        string temp = mapping[s];
        if (temp != s) return getRoot(temp, mapping);
        else return temp;
    }
};






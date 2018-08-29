

/*
Given two sentences words1, words2 (each represented as an array of strings),
and a list of similar word pairs pairs, determine if two sentences are similar.

For example, words1 = ["great", "acting", "skills"] and words2 = ["fine", "drama", "talent"] 
are similar, if the similar word pairs are pairs = [["great", "good"], ["fine", "good"], ["acting","drama"], ["skills","talent"]].

Note that the similarity relation is transitive. For example, if "great" and "good" are 
similar, and "fine" and "good" are similar, then "great" and "fine" are similar.

Similarity is also symmetric. For example, "great" and "fine" being similar is the same 
as "fine" and "great" being similar.

Also, a word is always similar with itself. For example, the sentences words1 = ["great"], words2 = ["great"], 
pairs = [] are similar, even though there are no specified similar word pairs.

Finally, sentences can only be similar if they have the same number of words. So a sentence like
words1 = ["great"] can never be similar to words2 = ["doubleplus","good"].

*/







//slower union find (why is this slower)
class Solution {
public:
    struct node
    {
        int rank;
        node* parent;
    };
    unordered_map<string, node*> m;
    node* make_set(const string& s)
    {
        if (m.find(s) != m.end()) return m[s];
        node* p = new node;
        p->rank = 1;
        p->parent = p;
        m[s] = p;
        return p;
    }
    node* find(node* n)
    {
        if (n->parent != n)
            n->parent = find(n->parent);
        return n->parent;
    }
    void uni(node* x, node* y)
    {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (x->rank < y->rank) swap(x, y);
        y->parent = x;
        x->rank = max(x->rank, y->rank + 1);
    }
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
        if (words1.size() != words2.size()) return false;
        for (auto pair : pairs)
        {
            node* f = make_set(pair.first);
            node* s = make_set(pair.second);
            uni(f, s);
        }
        for (int i = 0; i < words1.size(); i++)
        {
            if (words1[i] == words2[i]) continue;
            node* w1 = find(make_set(words1[i]));
            node* w2 = find(make_set(words2[i]));
            if (w1 != w2) return false;
        }
        return true;
    }
};

//slightly faster
class UF{
    vector<int> ar,sz;
public:
    UF(int n){
        ar.resize(n);
        sz.resize(n);
        for(int i = 0; i < n; i++){
            ar[i] = i;
            sz[i] = 1;
        }
    }
    bool find(int A, int B){
        return root(A) == root(B);
    }
    void weighted_union(int A,int B){
        int root_A = root(A), root_B = root(B);
        if(sz[root_A] < sz[root_B]){
            ar[root_A]  = ar[root_B];
            sz[root_B] += sz[root_A];
        }
        else{
            ar[root_B]  = ar[root_A];
            sz[root_A] += sz[root_B];
        }
    }
    int root (int i){
        while(ar[i] != i){
            ar[i] = ar[ar[i]]; 
            i = ar[i]; 
        }
        return i;
    }
};
class Solution {
public:
    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
        if (words1.size() != words2.size()) return false;
        unordered_map<string, int> index;
        int count = 0;
        UF dsu(2 * pairs.size());
        for (auto &pairpair: pairs) {
            if (index.find(pairpair.first) == index.end()) 
                index[pairpair.first] = count++;
            if (index.find(pairpair.second) == index.end()) 
                index[pairpair.second] = count++;
             
            dsu.weighted_union(index[pairpair.first], index[pairpair.second]);
        }

        for (int i = 0; i < words1.size(); i++) {
            if (words1[i] == words2[i]) continue;
            if (index.find(words1[i]) == index.end() or index.find(words2[i]) == index.end() ) {
                return false;
            }
            if ( !dsu.find( index[words1[i]], index[words2[i]] ) ) {
                return false;
            }
        }
        return true;
    }
};



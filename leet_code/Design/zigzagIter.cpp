/*
Given two 1d vectors, implement an iterator to return their elements alternately.
For example, given two 1d vectors:
v1 = [1, 2]
v2 = [3, 4, 5, 6]
By calling next repeatedly until hasNext returns false, the order of elements returned by 
next should be: [1, 3, 2, 4, 5, 6].
Follow up: What if you are given k 1d vectors? How well can your code be extended to such cases?
*/


class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        v.push_back(v1);
        v.push_back(v2);
        i=0;
        j=0;
    }

    int next() {        
        return i<=j ? v[0][i++]:v[1][j++];                    
    }

    bool hasNext() {
        if(i >= v[0].size()) i = INT_MAX;
        if(j >= v[1].size()) j = INT_MAX;
        return !(i >= v[0].size() && j >=v[1].size());
    }
private:
    vector<vector<int>> v;
    int i;
    int j;
};






//SOlution using queue
class ZigzagIterator {
private:
    queue<int> myQ;
    
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        
        int i, j = 0;
        
        while (i < v1.size() && j < v2.size()) {
            myQ.push(v1[i++]);
            myQ.push(v2[j++]);
        }
        
        while (i < v1.size()) {
            myQ.push(v1[i++]);
        }
        
        while (j < v2.size()) {
            myQ.push(v2[j++]);
        }
        
    }

    int next() {
        if (hasNext()) {
            int val = myQ.front();
            myQ.pop();
            return val;
        }
    }

    bool hasNext() {
        return myQ.size();
    }
};

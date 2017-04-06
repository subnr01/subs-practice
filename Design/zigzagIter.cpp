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
        if (v1.size() != 0)
            Q.push(make_pair(v1.begin(), v1.end()));
        if (v2.size() != 0)
            Q.push(make_pair(v2.begin(), v2.end()));
    }

    int next() {
        vector<int>::iterator it = Q.front().first;
        vector<int>::iterator endIt = Q.front().second;
        Q.pop();
        if (it + 1 != endIt)
            Q.push(make_pair(it+1, endIt));
        return *it;
    }

    bool hasNext() {
        return !Q.empty();
    }
private:
    queue<pair<vector<int>::iterator, vector<int>::iterator>> Q;
};


//Another solution
class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        bs[0] = v1.begin(), bs[1] = v2.begin();
        es[0] = v1.end(), es[1] = v2.end();
        p = 0;
    }
  
    int next() {
        int elem;
        if (bs[0] == es[0]) elem = *bs[1]++;
        else if (bs[1] == es[1]) elem = *bs[0]++;
        else {
            elem = *bs[p]++;
            p = (p + 1) % 2;
        }
        return elem;
    }

    bool hasNext() {
        return bs[0] != es[0] || bs[1] != es[1];
    }
private:
    int p; 
    vector<int>::iterator bs[2], es[2]; 
};

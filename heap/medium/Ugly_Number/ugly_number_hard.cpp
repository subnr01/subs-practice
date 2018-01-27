/*

Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 
For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.

Note that 1 is typically treated as an ugly number, and n does not exceed 1690.


*/

struct Solution {
    int nthUglyNumber(int n) {
        vector <int> results (1,1);
        int i = 0, j = 0, k = 0;
        while (results.size() < n)
        {
            results.push_back(min(results[i] * 2, min(results[j] * 3, results[k] * 5)));
            if (results.back() == results[i] * 2) ++i;
            if (results.back() == results[j] * 3) ++j;
            if (results.back() == results[k] * 5) ++k;
        }
        return results.back();
    }
};


//USing heap

class Solution {
public:
    int nthUglyNumber(int n) {
        long long ret = 0;
        priority_queue<long long, vector<long long>, greater<long long>> s;
        s.push(1);
        for (int i = 0; i < n; ++ i){
            while (s.top() == ret) s.pop();
            ret = s.top();
            s.pop();
            s.push(ret * 2);
            s.push(ret * 3);
            s.push(ret * 5);
        }
        return ret;
    }
};


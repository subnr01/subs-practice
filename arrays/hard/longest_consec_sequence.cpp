/*

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.


*/


class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        if (num.size() == 0) {
            return 0;
        }
        unordered_set<int> record(num.begin(),num.end());
        int res = 1;
        for(int n : num){
            if(record.find(n)==record.end()) continue;
            record.erase(n);
            int prev = n-1,next = n+1;
            while(record.find(prev)!=record.end()) record.erase(prev--);
            while(record.find(next)!=record.end()) record.erase(next++);
            res = max(res,next-prev-1);
        }
        return res;
    }
};


//Another similar soln (if you do not like erase)
int longestConsecutive(const vector<int> &num) {
    unordered_set<int> s(num.begin(), num.end()), searched;
    int longest = 0;
    for (int i: num) {
        if (searched.find(i) != searched.end()) continue;
        searched.insert(i);
        int j = i - 1, k = i + 1;
        while (s.find(j) != s.end()) searched.insert(j--);
        while (s.find(k) != s.end()) searched.insert(k++);
        longest = max(longest, k - 1 - j);
    }
    return longest;
}

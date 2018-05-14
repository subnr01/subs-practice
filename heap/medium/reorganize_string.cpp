/*
Given a string S, check if the letters can be rearranged so that two characters that are
adjacent to each other are not the same.

If possible, output any possible result.  If not possible, return the empty string.

Example 1:

Input: S = "aab"
Output: "aba"
Example 2:

Input: S = "aaab"
Output: ""

*/


//Related topics: heap and sort.

//USing heap
class Solution {
public:
    string reorganizeString(string S) {
        
        unordered_map<char, int> m;
        int len = S.size();
        string res;
        
        for (auto elem: S)
        {
            m[elem]++;
        }
        
        
        priority_queue<pair<int, char>> pq;
        
        for (auto elem: m)
        {
            if (elem.second > (len + 1)/2) {
                return res;
            }
            
            pq.push(make_pair(elem.second, elem.first));
            
        }
        //We take the top 2 and put it inside the string and
        //keep on doing that until we reach one.
        // We have to take 2 at a time, as they have to be the top
        //two and different. If we take one at a time, then we may 
        // be inserting the same element mulutple times
        while (pq.size() >= 2)
        {
            auto one = pq.top();
            res += one.second;
            pq.pop();
            auto two = pq.top();
            res += two.second;
            pq.pop();
            
            one.first--;
            two.first--;
            if (one.first) {
                pq.push(one);
            }
            if (two.first) {
                pq.push(two);
            }
            
        }
        
        if (pq.size())
        {
            res += pq.top().second;
        }
        
        return res;
        
        
    }
};




//Using sort ( Leetcode soln was in java, I 
// successfully converted to C++, yeyeyeye)
class Solution {
public:
    string reorganizeString(string S) {
        int n = S.length();
        vector<int> counts(26);
        for (auto c: S) {
            counts[c - 'a'] += 100;
        }
        for (int i = 0; i < 26; i++)
        {
            counts[i] += i;
        }
        sort(counts.begin(), counts.end());
        
        int t = 1;
        string ans(n, '*');
        
        for (auto code: counts)
        {
            int ct = code/100;
            char ch = (char) ('a' + (code % 100));
            if (ct >(n + 1)/2) {
                return "";
            }
            for (int i = 0; i < ct; i++)
            {
                if (t >= n) {
                    t = 0;
                }
                ans[t] = ch;
                t += 2;
            }
        }
        return ans;
    }
};

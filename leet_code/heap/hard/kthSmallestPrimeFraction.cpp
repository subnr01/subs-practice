/*
A sorted list A contains 1, plus some number of primes.  Then, for every p < q in the list,
we consider the fraction p/q.

What is the K-th smallest fraction considered?  Return your answer as an array of ints,
where answer[0] = p and answer[1] = q.

Examples:
Input: A = [1, 2, 3, 5], K = 3
Output: [2, 5]
Explanation:
The fractions to be considered in sorted order are:
1/5, 1/3, 2/5, 1/2, 3/5, 2/3.
The third fraction is 2/5.

Input: A = [1, 7], K = 1
Output: [1, 7]

*/

//Related topics: Binary search and heap

//Prioirity queue soln
/*

it is like find k-th smallest element in n sorted array, which has a classic solution using priority_queue

consider an input of [n1, n2, n3, n4, n5], the possible factors are:
[n1/n5, n1/n4, n1/n3, n1/n2, n1/n1]
[n2/n5, n2/n4, n2/n3, n2/n2]
[n3/n5, n3/n4, n3/n3]
[n4/n5, n4/n4]
[n5/n5]

*/

//Priority queue soln has heavy overhead (800 ms)
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        priority_queue<pair<double, pair<int,int>>>pq;
        for(int i = 0; i < A.size(); i++)
            pq.push({-1.0*A[i]/A.back(), {i,A.size()-1}});
        while(--K > 0)
        {
            pair<int,int> cur = pq.top().second;
            pq.pop();
            cur.second--;
            pq.push({-1.0*A[cur.first]/A[cur.second], {cur.first, cur.second}});
        }
        return {A[pq.top().second.first], A[pq.top().second.second]};
    }
};


//Binary search (14ms)
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        double l=0;
        double r=1;
        while(true){
            double mid = (l+r)/2;
            vector<int> res = countSmaller(A,mid);
            
            if(res[0]>K){
                r=mid;
            }else if(res[0]<K){
                l=mid;
            }else{
                vector<int> ans = {res[1],res[2]};
                return ans;
            }
        }
    }
    
    vector<int> countSmaller(vector<int>& A,double mid){
        int p =0;
        int q = 1;
        
        int count = 0;
        int j=0;
        for(int i=0;i<A.size();i++){
            while(j<A.size() && A[i]>mid*A[j]){
                j++;
            }
            count += A.size()-j;
            
            if(j<A.size() && p*A[j]<q*A[i]){
                p=A[i];
                q=A[j];
            }
        }
        
        vector<int> res = {count,p,q};
        return res;
    }
};


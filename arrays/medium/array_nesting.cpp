/*
A zero-indexed array A of length N contains all integers from 0 to N-1. Find and return
the longest length of set S, where S[i] = {A[i], A[A[i]], A[A[A[i]]], ... } subjected to the rule below.

Suppose the first element in S starts with the selection of element A[i] of index = i, the
next element in S should be A[A[i]], and then A[A[A[i]]]… By that analogy, we stop adding right before a duplicate element occurs in S.

Example 1:
Input: A = [5,4,0,3,1,6,2]
Output: 6
Explanation: 
A[0] = 5, A[1] = 4, A[2] = 0, A[3] = 3, A[4] = 1, A[5] = 6, A[6] = 2.

One of the longest S[K]:
S[0] = {A[0], A[5], A[6], A[2]} = {5, 6, 2, 0}

*/

/*
Soln

The idea is to, start from every number, find circles in those index-pointer-chains, 
every time you find a set (a circle) mark every number as visited (-1) so that next time you won't step on it again.
C++
*/


class Solution {
public:
    int arrayNesting(vector<int>& a) {
        size_t maxsize = 0;
        for (int i = 0; i < a.size(); i++) {
            size_t size = 0;
            //Do not forget the equals to 0 comparison here
            for (int k = i; a[k] >= 0; size++) {
                int ak = a[k];
                a[k] = -1; // mark a[k] as visited;
                k = ak;
            }
            maxsize = max(maxsize, size);
        }

        return maxsize;
    }
};
/*
Time complexity : O(n)O(n). 
Space complexity : O(1)O(1). Constant Space is used.
*/

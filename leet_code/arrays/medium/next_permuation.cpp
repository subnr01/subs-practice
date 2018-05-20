/*

Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place, do not allocate extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1


*/


//https://stackoverflow.com/questions/11483060/stdnext-permutation-implementation-explanation
/*
This is key to understanding the algorithm. We only change the position of a "digit" 
when everything to the right is in descending order because if it isn't in descending
order then there are still more permutations to go 

How to do it.

Find p, p is the first digit from the end which is lesser than the number to the right.
if p is not there, then reverse the entire array.
if p is there, then find q. q is the first number that is greater than p from the right.
swap p and q.
reverse(p+1, end)
*/

// For example
/// 1432 --> 2134 because p = 1 and q = 2 in 1432 which on swapping gives 2431. and numbers
/// are descending after 2, so reverse gives 2134.

class Solution {
public:

void nextPermutation(vector<int>& a)
{
        size_t n = a.size();
        if (n <= 1) {
            return;
        }
        int p = -1;
        int q = -1;
        
        for (int i = n - 2; i >= 0; i--)
        {
            if (a[i] < a[i+1]) {
                p = i;
                break;
            }
        }
        
        if (p == -1) {
            reverse(a.begin(), a.end());
            return;
        }
        
        for (int i = n - 1; i > p; i--)
        {
            if (a[i] > a[p]) {
                q = i;
                break;
            }
        }
        
        swap (a[p], a[q]);
        reverse(a.begin() + p + 1, a.end());
        return;
        
    }
};


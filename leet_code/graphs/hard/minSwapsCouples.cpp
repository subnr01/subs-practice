/*
N couples sit in 2N seats arranged in a row and want to hold hands. We want to know 
the minimum number of swaps so that every couple is sitting side by side. 
A swap consists of choosing any two people, then they stand up and switch seats.

The people and seats are represented by an integer from 0 to 2N-1, the couples
are numbered in order, the first couple being (0, 1), the second couple
being (2, 3), and so on with the last couple being (2N-2, 2N-1).

The couples' initial seating is given by row[i] being the value of the
person who is initially sitting in the i-th seat.

Example 1:

Input: row = [0, 2, 1, 3]
Output: 1
Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
Example 2:

Input: row = [3, 2, 0, 1]
Output: 0
Explanation: All couples are already seated side by side.

*/

//Related topics: Union Find, graph, greedy

//Solution 1
//https://leetcode.com/problems/couples-holding-hands/discuss/113362/JavaC++-O(N)-solution-using-cyclic-swapping

//4 ms

int minSwapsCouples(vector<int>& row) {
    int res = 0, N = row.size();
        
    vector<int> ptn(N, 0);
    vector<int> pos(N, 0);
        
    for (int i = 0; i < N; i++) {
        ptn[i] = (i % 2 == 0 ? i + 1 : i - 1);
        pos[row[i]] = i;
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = ptn[pos[ptn[row[i]]]]; i != j; j = ptn[pos[ptn[row[i]]]]) {
	    swap(row[i], row[j]);
            swap(pos[row[i]], pos[row[j]]);
	    res++;
	}
    }
        
    return res;
}


//Greedy soln ( 6 ms)
class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        if(row.size() <=2){
            return 0;
        }
        
        vector<int> pos(row.size());
        // This is the key of the solution, with this position hash map, we can quickly find out where the couple is. 
        for(size_t i = 0; i< row.size(); i++){
            pos[row[i]] = i;
        }
        
        int count = 0;
        for(size_t i = 0; i < row.size(); i+=2){
            int &me = row[i];
            int myCouple = (me & 1) ? me - 1: me + 1;
            if(row[i+1] != myCouple){
                count++;
                int neighbor = row[i+1];
                // Swap values
                row[i+1] = myCouple;
                row[pos[myCouple]] = neighbor;
                pos[neighbor] = pos[myCouple];
                // No need to update my couple's position, he/she is by my side now :)
            }
        }
        
        return count;
    }
};

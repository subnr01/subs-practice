/*
The set [1,2,3,…,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order,
We get the following sequence (ie, for n = 3):

"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Note: Given n will be between 1 and 9 inclusive.

*/

//https://discuss.leetcode.com/topic/17348/explain-like-i-m-five-java-solution-in-o-n


class Solution {
public:
     string getPermutation(int n, int k) {
        string str;
        string result;
        
        //Taking example n = 3, k =3
          
        int i,  mod;
        mod = 1;
        for (i = 1; i <= n; i++){
            mod = i * mod;
            str += to_string(i);
        }
        //Change k to reflect the index
        k--;
        
        //mod = 6, k = 2
        for (i = 0; i < n; i++){
            mod /= n - i;  //(mod = (n-1)!
            int curindex  = k/mod; //k/(n-1)!
            k = k % mod;  //2%mod
            result.push_back(str[curindex]);
            str.erase(str.begin()+curindex);
            
        }
         
        return result;
    }
    
};

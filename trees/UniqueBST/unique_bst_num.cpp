



/*

https://discuss.leetcode.com/topic/8398/dp-solution-in-6-lines-with-explanation-f-i-n-g-i-1-g-n-i/2

*/


 Number of binary search trees = 
                     (Number of ways root can be choosen)*
                     (Number of Left binary search sub-trees) *                 
                     (Number of Right binary search sub-trees)                                                  
Now, since there are "n" nodes in BST and let, the number of BST be represented by C(n) for n elements.

We can find the number of BSTs recursively as :
choose 1 as root, no element  on the left sub-tree. n-1 elements on the right sub-tree.
Choose 2 as root, 1 element  on the left sub-tree. n-2 elements on the right sub-tree.
Choose 3 as root, 2 element on the left sub-tree. n-3 elements on the right sub-tree.

Similarly, for i-th element as the root, i-1 elements on the left and n-i on the right.

These sub-trees are also BSTs so we can write :

C(n) = C(0)C(n-1) + C(1)C(n-2) + .....+ C(i-1)C(n-i)..... + C(n-1)C(0)
    
    
    
    

class Solution {
public:
    int numTrees(int n) {
       int G[(n+1)] = {0};
        G[0] = G[1] = 1;
        for(int i=2; i<=n; ++i) {
    	for(int j=1; j<=i; ++j) {
    		G[i] += G[j-1] * G[i-j];
    	}
    }

    return G[n];
   }
        
    
};

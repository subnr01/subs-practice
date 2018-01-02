/*
Given an index k, return the kth row of the Pascal's triangle.
For example, given k = 3,
Return [1,3,3,1].
*/


class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> vi(rowIndex + 1);
       	vi[0] = 1;
        for (int i = 0; i <= rowIndex ; ++i)
        {
		/*
		See how j decrements from i to 0.
		j[2] = 1 + 2;
		j[1] = 2 + 1;
		*/
        	for (int j = i; j > 0; --j)
        	{
	        	vi[j] = vi[j] + vi[j-1];
        	}
        }
        return vi;
    }
};

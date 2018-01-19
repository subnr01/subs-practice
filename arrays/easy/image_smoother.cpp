/*

Given a 2D integer matrix M representing the gray scale of an image, you need to design a smoother to make the gray scale of each cell becomes the average gray scale (rounding down) of all the 8 surrounding cells and itself. If a cell has less than 8 surrounding cells, then use as many as you can.

Example 1:
Input:
[[1,1,1],
 [1,0,1],
 [1,1,1]]
Output:
[[0, 0, 0],
 [0, 0, 0],
 [0, 0, 0]]
Explanation:
For the point (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
For the point (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
For the point (1,1): floor(8/9) = floor(0.88888889) = 0

*/

class Solution {
private: 
    bool valid(int i,int j,vector<vector<int>>& M)
    {
        if (i >=0 && i<M.size() && j>=0 && j<M[0].size())
            return true;
        return false;
    }
    
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
        vector<vector<int>> res;
        if (M.size()==0 || M[0].size()==0)
            return res;

        for (int i = 0; i< M.size(); i++)
        {            
            vector<int> cur;
            for(int j = 0; j< M[0].size(); j++)
            {
                int total = 0;
                int count = 0;
                for (int x = -1; x<2;x++)
                {
                    for (int y = -1; y<2; y++)
                    {
                        if(valid(i+x,j+y,M))
                        {
                            count++;
                            total +=M[i+x][j+y];
                        }
                    }
                }
                cur.push_back(total/count);
            }
            res.push_back(cur);
        }
        return res; 
    }
};

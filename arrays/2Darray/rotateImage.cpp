/*

Rotate image by 90

*/




/*
Rotate image

1 2 
3 4

Ans
3, 1
4, 2

3*3 example
1 2 3
4 5 6
7 8 9

Ans:
7 4 1
8 5 2
9 6 3
*/

void rotate(vector<vector<int>>& matrix) {
        const int n = matrix.size();

        for(int i = 0 ;i < n/2 ; ++i)
        	for (int j = 0; j < n; ++j)
        	 	swap( matrix[i][j], matrix[n - 1 - i][j] );


3 4 
1 2 



        	 for(int i = 0;i < n ; ++i)
        	 	for (int j = i + 1; j < n; ++j)
        	 		swap(matrix[i][j], matrix[j][i]);

3 1
4 2


}

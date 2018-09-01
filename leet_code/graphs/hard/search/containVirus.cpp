/*
A virus is spreading rapidly, and your task is to quarantine the infected area by installing walls.

The world is modeled as a 2-D array of cells, where 0 represents uninfected cells, and 1 represents cells
contaminated with the virus. A wall (and only one wall) can be installed between any two 4-directionally adjacent cells, on the shared boundary.

Every night, the virus spreads to all neighboring cells in all four directions unless blocked by a wall. 
Resources are limited. Each day, you can install walls around only one region -- the affected area (continuous block of infected cells) that threatens the most uninfected cells the following night. There will never be a tie.

Can you save the day? If so, what is the number of walls required? If not, and the world becomes fully 
infected, return the number of walls used.

Example 1:
Input: grid = 
[[0,1,0,0,0,0,0,1],
 [0,1,0,0,0,0,0,1],
 [0,0,0,0,0,0,0,1],
 [0,0,0,0,0,0,0,0]]
Output: 10
Explanation:
There are 2 contaminated regions.
On the first day, add 5 walls to quarantine the viral region on the left. The board after the virus spreads is:

[[0,1,0,0,0,0,1,1],
 [0,1,0,0,0,0,1,1],
 [0,0,0,0,0,0,1,1],
 [0,0,0,0,0,0,0,1]]

On the second day, add 5 walls to quarantine the viral region on the right. The virus is fully contained.
Example 2:
Input: grid = 
[[1,1,1],
 [1,0,1],
 [1,1,1]]
Output: 4
Explanation: Even though there is only one cell saved, there are 4 walls built.
Notice that walls are only built on the shared boundary of two different cells.
Example 3:
Input: grid = 
[[1,1,1,0,0,0,0,0,0],
 [1,0,1,0,1,1,1,1,1],
 [1,1,1,0,0,0,0,0,0]]
Output: 13
Explanation: The region on the left only builds two new walls.
Note:
The number of rows and columns of grid will each be in the range [1, 50].
Each grid[i][j] will be either 0 or 1.
Throughout the described process, there is always a contiguous viral region that will infect strictly more uncontaminated squares in the next round.

*/


//Check other solns also, this is a DFS solition
class Solution {
public:
	int containVirus(vector<vector<int>>& grid) {
		m = grid.size();
		if (m == 0)
			return 0;
		n = grid[0].size();
		if (n == 0)
			return 0;

		int walls = 0;
		while (true)
		{
			vector<vector<int> > flags(m, vector<int>(n, 0));
			vector<vector<int> > affectedAreas;
			int affected = 0;
			int f = 1;
			int wall = 0;
			int maxf = 0;
			int maxi = 0, maxj = 0;
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (grid[i][j] == 0 || flags[i][j] != 0)
						continue;
					int w = 0;
					vector<int> oneArea;
					int a = helper(grid, i, j, flags, oneArea, w, f);
					if (oneArea.size() > affected)
					{
						affected = oneArea.size();
						wall = w;
						maxf = f;
						maxi = i;
						maxj = j;
					}
					f++;
					affectedAreas.push_back(oneArea);
				}
			}
			if (wall == 0)
				break;
			walls += wall;
			setInActive(grid, maxi, maxj);
			for (int k = 0; k < affectedAreas.size(); k++)
			{
				//if (k == maxf - 1)
				//	continue;
				vector<int>& b = affectedAreas[k];
                if(b.size() == affected)
                    continue;
				for (int p : b)
				{
					int x = p / n;
					int y = p%n;
					grid[x][y] = 1;
				}
			}
			

		}
		return walls;
	}

private:
	int m, n;
	int helper(vector<vector<int>>& grid, int i, int j,
		vector<vector<int>>& flags, vector<int>& areas, int& wall, int f) {
		if (i < 0 || i >= m || j < 0 || j >= n || flags[i][j] == f)
			return 0;
		if (grid[i][j] == -1)
		{
			return 0;
		}
		int area = 0;
		if (grid[i][j] == 0)
		{
			if (flags[i][j] != -1*f)
			{
				flags[i][j] = -1 * f;
				area++;
				areas.push_back(i*n + j);
			}
			wall++;
			return area;
		}
		flags[i][j] = f;
		area += helper(grid, i - 1, j, flags, areas, wall, f);
		area += helper(grid, i + 1, j, flags, areas, wall, f);
		area += helper(grid, i, j + 1, flags, areas, wall, f);
		area += helper(grid, i, j - 1, flags, areas, wall, f);
		return area;
	}

	void setInActive(vector<vector<int>>& grid, int i, int j) {
		if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] != 1)
			return;
		grid[i][j] = -1;
		setInActive(grid, i + 1, j);
		setInActive(grid, i - 1, j);
		setInActive(grid, i, j + 1);
		setInActive(grid, i, j - 1);
	}
};


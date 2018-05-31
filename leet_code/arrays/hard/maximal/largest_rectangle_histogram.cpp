/*

Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, 
find the area of largest rectangle in the histogram.

*/

//WHAT ABOUT BRUTE FORCE SOLUTION
//THE BRUTE FORCE SOLUTION IS A O(n*2)solution.
//Basically we start from every bar and move right 
//and stop if we get a lesser height and same
//way for left as well.
//The difference between (left - right)*height will 
//give the largest area.
//TLE for some reason
class Solution {
public:
    //brute force, O(n^2)
    int largestRectangleArea(vector<int> &height) {
        int n = height.size();
        if (n == 0) {
            return 0;
        }
        int minHeight = 0;
        int maxArea = 0;
        
        for(int i = 0; i < height.size(); i++) {
            minHeight = height[i];
            maxArea = max(maxArea, minHeight * 1);
            for(int j = i + 1; j < height.size(); j++) {
                minHeight = min(minHeight, height[j]);
                maxArea = max(maxArea, minHeight * (j - i + 1));
            }
        }
        return maxArea;
    }
    
};



//Some good explanation under
//https://stackoverflow.com/questions/4311694/maximize-the-rectangular-area-under-histogram

/*
This problem comes down to basically get the height of the smallest bar and
width of the entire histogram stretch unless you have another slightly bigger one
that can marginally give more area.

For example:
{2,4,2,4} we get 2(smallest height) * width (4 elements) = 8.
{2,4,2,1} we get 2(smallest height) * widht (3 elements) = 6.
Note in the second example, even if 1 is the smallest height 1*4 < 2*3
which emphasises the above point. Another corner case where
we have really a very tall building that can surpass the 
width of the entire canvass.
{2,14,2,4}  = 14

So how do we achieve this?

There is a trick logic.

1. push into the stack until you find a bar of lesser height.
2. Pop the top, now the top signifies the tallest building and the area of the tallest building
is height * 1 unit ( this is constant and is calculated by (s.pop(); i - s.top() - 1).
3. After every pop peration, we do not increment i (THIS IS KEY) because we want to push i again and get the 
height of the small building into the stack. The last element in the stack will probably be the smallest
height and will be mulitplied finally with the entire stretch
*/
////O(n) solution , but not modifying the input hence slightly slower.
class Solution {
public:
    int largestRectangleArea(vector<int>& height) {
    height.push_back(0);
    const int size_h = height.size();
    stack<int> stk;
    int i = 0, max_a = 0;
    while (i < size_h) {
        if (stk.empty() || height[i] >= height[stk.top()]) {
          stk.push(i);
          i++;  
        } else {
            int h = stk.top();
            stk.pop();
            int H = height[h];
            int W = (stk.empty() ? i : i - stk.top() - 1);
            max_a = max(max_a, H * W);
        }
    }
        
    if (!stk.empty())
    {
        int p = stk.top();
        int H = height[p];
        int W = i - stk.top() - 1;
        max_a = max(max_a, H * W);
        stk.pop();
        
    }
    return max_a;
 }
};



//O(n) solution
//faster
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int ans = 0;
        stack<int> index;
	//MODIYFING THE VECTOR HERE
	heights.push(0);
        for (int i = 0; i <= heights.size(); i++) {
            while (!index.empty() && (heights[index.top()] > heights[i] || i == heights.size())) {
                int h = heights[index.top()];
                index.pop();
                if (index.empty()) {
                    ans = max(ans, h * i);
                } else {
                    ans = max(ans, h * (i - index.top() - 1));
                }
            }
            index.push(i);
        }
        return ans;
    }
};


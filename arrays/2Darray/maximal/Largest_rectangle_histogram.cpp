/*

Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, 
find the area of largest rectangle in the histogram.

*/

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
    return max_a;
}

//Without modifying the vector

/*

Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, 
find the area of largest rectangle in the histogram.

*/

int largestRectangleArea(vector<int>& height) {
    height.push_back(0);
    const int size_h = height.size();
    stack<int> stk;
    int i = 0, max_a = 0;
    while (i < size_h) {
        if (stk.empty() || height[i] >= height[stk.top()]) {
          stk.push(i++);
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

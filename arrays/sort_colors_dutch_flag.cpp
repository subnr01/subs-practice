/*
Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

*/



class Solution {
    public:
    void sortColors(vector<int>& a) 
    {
        int tmp = 0, low = 0, mid = 0, high = a.size() - 1;
    
        while(mid <= high)
        {
            switch(a[mid])
            {
                case 0: swap(a[mid], a[low]);
                        mid++;
                        low++;
                        break;
                
                
                case 1: mid++; break;
                
                
                case 2: swap(a[mid],a[high]);
                        high--;
                        break;
            }
        }
    }
};

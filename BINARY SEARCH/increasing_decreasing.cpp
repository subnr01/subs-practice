
/* 
Finding the maximim element in an increasing and decreasing array
*/

int findMaximum(int arr[], int low, int high)
{
 
   /* Base Case: Only one element is present in arr[low..high]*/
   if (low == high)
     return arr[low];
 
   /* If there are two elements and first is greater then
      the first element is maximum */
   if ((high == low + 1) && arr[low] >= arr[high])
      return arr[low];
 
   /* If there are two elements and second is greater then
      the second element is maximum */
   if ((high == low + 1) && arr[low] < arr[high])
      return arr[high];
 
   int mid = (low + high)/2;   /*low + (high - low)/2;*/
 
   /* If we reach a point where arr[mid] is greater than both of
     its adjacent elements arr[mid-1] and arr[mid+1], then arr[mid]
     is the maximum element*/
   if ( arr[mid] > arr[mid + 1] && arr[mid] > arr[mid - 1])
      return arr[mid];
 
   /* If arr[mid] is greater than the next element and smaller than the previous 
    element then maximum lies on left side of mid */
   if (arr[mid] > arr[mid + 1] && arr[mid] < arr[mid - 1])
     return findMaximum(arr, low, mid-1);
   else // when arr[mid] is greater than arr[mid-1] and smaller than arr[mid+1]
     return findMaximum(arr, mid + 1, high);
}



/*

Searching in an array that is first increasing and then decreasing


The key is to start by finding the index of the minimum element. Once you have that, you can do a binary search in the left-hand (decreasing) part, and a binary search in the right-hand (increasing) part. Since the binary searches can be done in log time, you can do the whole thing in log time provided that you can find the minimum element in log time.


Fortunately you can also do that with a binary search. For any place in the array that you consider, if the following element is greater, then you're in the right-hand (increasing) part; and if it's smaller, then you're in the left-hand (decreasing) part. This is enough to allow you to perform a binary search to find the minimum.
*/


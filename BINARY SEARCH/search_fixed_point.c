

/*
Given an array of n distinct integers sorted in ascending order, write a function that returns a Fixed Point 
in the array, if there is any Fixed Point present in array, else returns -1. Fixed Point in an array is an 
index i such that arr[i] is equal to i. Note that integers in array can be negative.



*/




int binarySearch(int arr[], int low, int high)
{
    if(high >= low)
    {
        int mid = (low + high)/2;  /*low + (high - low)/2;*/
        if(mid == arr[mid])
            return mid;
        if(mid > arr[mid])
            return binarySearch(arr, (mid + 1), high);
        else
            return binarySearch(arr, low, (mid -1));
    }
 
    /* Return -1 if there is no Fixed Point */
    return -1;
}

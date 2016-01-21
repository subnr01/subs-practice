/*
Given an array of integers, every element appears twice except for one.
Find that single one
*/




int singleNumber(int A[], int n) {
    int result = 0;
    for (int i = 0; i<n; i++)
    {
        result ^=A[i];
    }
    return result;
}

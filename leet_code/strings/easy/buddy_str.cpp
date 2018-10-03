
/*
Given two strings A and B of lowercase letters, return true if and only if we can swap two letters in A so that the result equals B

Example 1:
Input: A = "ab", B = "ba"
Output: true
Example 2:
Input: A = "ab", B = "ab"
Output: false
*/
bool buddyStrings(string A, string B) 
{
    int m = A.size();
    int n = B.size();

    if (m != n) {
        return false;
    }

    int sz = unordered_set<char>(A.begin(), A.end()).size();

    if (A == B && sz < n) {
        return true;
    }

    vector<int> index_diff;

    for (int i = 0; i < m; i++)
    {
        if (A[i] != B[i])
        {
            index_diff.push_back(i);
            if (index_diff.size() > 2) {
                return false;
            }
        }

    }

    return index_diff.size() == 2 && 
           A[index_diff[0]] == B[index_diff[1]] &&
           A[index_diff[1]] == B[index_diff[0]];


}

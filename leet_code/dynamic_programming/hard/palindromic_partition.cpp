
/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

Example:

Input: "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
*/


//77%
class Solution {
    public:
        int minCut(string s) {
            if(s.empty()) return 0;
            int n = s.size();
            vector<vector<bool>> pal(n,vector<bool>(n,false));
            vector<int> d(n);
            for(int i=n-1;i>=0;i--)
            {
                d[i]=n-i-1;
                for(int j=i;j<n;j++)
                {
                    if(s[i]==s[j] && (j-i<2 || pal[i+1][j-1]))
                    {
                       pal[i][j]=true;
                       if(j==n-1)
                           d[i]=0;
                       else if(d[j+1]+1<d[i])
                           d[i]=d[j+1]+1;
                    }
                }
            }
            return d[0];
        }
    };
    
    
    //94%
    class Solution
{
    public:
    
    int minCut( string s )
    {
        int n = s.size();
        if( n <= 1 )
            return 0;
        
        vector<int> cut( n + 1, 0 );
        
        for( int i = 0; i <= n; i++ )
            cut[i] = i - 1;
        
        for( int i = 0; i < n; i++ )
        {
            checkLeftRight( s, i, i, cut );
            checkLeftRight( s, i, i + 1, cut );
        }
        
        return cut[n];
    }
    
    void checkLeftRight( string s, int left, int right, vector<int> &cut )
    {
        while( left >= 0 && right < s.length() )
        {
            if( s[left] != s[right] )
                break;
            
            cut[right + 1] = min( cut[right + 1], cut[left] + 1 );
            
            left--;
            right++;
        }
    }
};

